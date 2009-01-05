//******************************************************************************
/**
 *  Used to control all apsects of sprites in this game. Including 
 *       memory access availability linked list
 */

#include "Sprites.h"
#include "Debug.h"

OAM_Entry Sprites::OAMCopy[MAX_SPRITES];
RotData* Sprites::rotData;

//      Define your statics

__attribute__((aligned(4))) int Sprites::sprite_pallet_index;

/// Create a linked list of sprite numbers that are available 
__attribute__((aligned(4))) SpritesAvailable* Sprites::sprites_available; 

/// Create linked list to GFX memory being used 
__attribute__((aligned(4))) SpriteGFX* Sprites::sprite_gfx;

int Sprites::gfx_memory_index;

//******************************************************************************
/**
 *   Create a sprite on the screen
 */

u8 Sprites::createSprite(int x, int y, int sprite_size_code, int color)
{

    u8 sprite_number = getNextAvailableSprite();

    // Check for invalid data
    if(sprite_number >= MAX_SPRITES || sprite_number == NO_SPRITES_LEFT)
    {

        return NO_SPRITES_LEFT;

    }

    setSpriteColorAndShape(spriteTypeToShape(sprite_size_code),color, 
            sprite_number);

    // Set up the sprite on the screen
    setSpritePosition(x, y, sprite_number);

    // Set the sprite size attribute in OAM
    setSpriteSize(spriteTypeToSize(sprite_size_code), sprite_number);

    //    Debug::printSetup();
    ////    u16* OAM16 = (u16*)OAM;
    //    iprintf("\x1b[0;0H sprite_number: %04x", sprite_number);
    //    iprintf("\x1b[1;0H OAMCopy[0].a[0]: %04x", OAMCopy[0].attribute[0]);
    //    iprintf("\x1b[2;0H OAMCopy[0].a[1]: %04x", OAMCopy[0].attribute[1]);
    //    iprintf("\x1b[3;0H OAMCopy[0].a[2]: %04x", OAMCopy[0].attribute[2]);
    //    
    //    iprintf("\x1b[4;0H OAMCopy[1].a[0]: %04x", OAMCopy[1].attribute[0]);
    //    iprintf("\x1b[5;0H OAMCopy[1].a[1]: %04x", OAMCopy[1].attribute[1]);
    //    iprintf("\x1b[6;0H OAMCopy[1].a[2]: %04x", OAMCopy[1].attribute[2]);
    //    
    //    iprintf("\x1b[7;0H OAMCopy[2].a[0]: %04x", OAMCopy[2].attribute[0]);
    //    iprintf("\x1b[8;0H OAMCopy[2].a[1]: %04x", OAMCopy[2].attribute[1]);
    //    iprintf("\x1b[9;0H OAMCopy[2].a[2]: %04x", OAMCopy[2].attribute[2]);
    return sprite_number;

}

//******************************************************************************
/**
 *  Add pallet data for sprite
 *       @param pallet pallet to place into memory
 *       @param size size in bytes
 *       @return pallet data index number
 */

int Sprites::addPalletData(unsigned char* pallet, int size)
{

    dmaCopy((const void*)pallet, (void*)SPRITE_PALETTE, size);

    //    memcpy(SPRITE_PALETTE,pallet, size);
    //    Debug::printSetup();
    //    u16* pallet_16 = (u16*)pallet;
    //    iprintf("\x1b[0;0H Pallet_mem: 0x%x pal_byte_size: %d: pal: %x", 
    //            SPRITE_PALETTE,size,pallet);
    //    int test_index = 0;
    //    iprintf("\x1b[1;0H *Pallet_mem[%d] = {0x%04x%04x..}",
    //            test_index,SPRITE_PALETTE[test_index], 
    //            SPRITE_PALETTE[test_index+1]);
    //    iprintf("\x1b[5;0H *pallet[%d] = {0x%04x%04x..}",
    //            test_index,pallet_16[test_index], pallet_16[test_index+1]);
    //

}

//******************************************************************************
/**
 *   Init the sprites system
 */

void Sprites::initSprites()
{

    // Make sure all GFX data starts at the beginning
    gfx_memory_index = 0;

    // Initialize all memory index to start of memory
    sprite_pallet_index = 0;

    disableAllSprites();
    // Set up the linked list of available sprites
    initSpritesAvailable();

}

//******************************************************************************
/**
 *       Disable all sprites
 */

void Sprites::disableAllSprites()
{

    // Initialy, Turn off all sprites
    int i;
    for(i =0; i < MAX_SPRITES; i++)
    {

        disableSprite(i);

    }   

}

//******************************************************************************
/**
 *   Initialize all sprites data structures
 */
 
void Sprites::initSpritesAvailable()
{

    // Map the sprite rotation data to proper memory 
    rotData = (RotData*)OAMCopy;

    // Initialy, Turn off all sprites
    disableAllSprites();
    sprites_available = (SpritesAvailable*)malloc(sizeof(SpritesAvailable));
    SpritesAvailable* current = sprites_available;

    // Set up sprites gfx being used (NULL when not being used)
    sprite_gfx = NULL;

    int i;
    // Populate all nodes, and GFX info
    for(i = 0; i < 128; i++)
    {

        current->next = (SpritesAvailable*)malloc(sizeof(SpritesAvailable));
        current->sprite_number = i;
        current = current->next;

    }

    // Append null to the end of the linked list
    current->next = (SpritesAvailable*)NULL;

}

//******************************************************************************
/**
 *   Update GFX memory block tracker with a new block of used memory
 *       @param begin_index the offset from GFX memory that this new block 
 *           will start at
 *       @param size the size of the new block
 */

bool Sprites::setGFXMemoryUsed(int begin_index, unsigned int size)
{

    // Create the new GFX tracking node
    SpriteGFX* new_gfx = (SpriteGFX*)malloc(sizeof(SpriteGFX));
    new_gfx->size = size;
    new_gfx->begin_index = begin_index;

    SpriteGFX* current = sprite_gfx;

    // Base condition: If the spritegfx tracker is null (no elements), 
    //      make new node first in list
    if(current == NULL)
    {

        sprite_gfx = new_gfx;
        sprite_gfx->next = NULL;
        return true;

    }

    // Now find a spot to place the link
    SpriteGFX* last = NULL;
    do
    {

        // Case of when current is larger than newGFX and newGFX needs to be 
        //      appended before current 
        if(current->begin_index > begin_index && 
                // also make sure the new block fits in this space
                last == NULL || (current->begin_index - 
                    last->begin_index+last->size) >= size)           
        {
 
            // Place new link in between current and current->next
            //      (Re-connect all links)
            if(last != NULL)
            {

                last->next = new_gfx;

            }
            new_gfx->next = current;
            // Since all our work is done, return
            return true;

        }

        // Case of where current->next is null, and newGFX is appended on 
        //      end of linked list
        else if(current->next == NULL)
        {

            current->next = new_gfx;
            new_gfx->next = NULL;

            // Since all our work is done, return (and give result of 
            //    bounds check)
            return checkGFXBounds(begin_index, size);

        }
        last = current;
        current = current->next;

    }while(current != NULL);

    //-----------------------------------------------------------
    // Since we were not able to find a suitable area to insert this,
    //      this should not happen, display error message
    //-----------------------------------------------------------
    Debug::printSetup();
    iprintf("\x1b[0;0H ERROR!!: GFX[%d],size=%d was not inserted!", 
            begin_index,size); 

    return false;

}

//******************************************************************************
/**
 *   Delete a GFX block (making it usable by the system)
 */

bool Sprites::freeGFXBlock(int begin_index)
{

    SpriteGFX* current = sprite_gfx;
    SpriteGFX* last = NULL;
    while(current != NULL)
    {

        // If the block to delete is found, arrange links and delete 
        //      this block
        if(current->begin_index = begin_index)
        {

            if(last != NULL)
            {
    
                last->next = current->next;

            }

            else
            {

                sprite_gfx = current->next;

            }

            free(current);

        }

        last = current;
        current = current->next;

    }

}

//******************************************************************************
/**
 *  Get the next available sprite number not being used (or NO_SPRITES_LEFT)
 */ 

u8 Sprites::getNextAvailableSprite()
{

    // If we reached the end of the linked list, return indication 
    //      no sprites are left
    if(sprites_available == NULL)
    {

        Debug::printSetup();
        iprintf("\x1b[0;0H ERROR NO SPRITES LEFT!! 128 used!");
        while(1);
        return NO_SPRITES_LEFT;

    }
    u8 to_return = sprites_available->sprite_number;
    // Erase the previous sprite number instance
    SpritesAvailable* to_free = sprites_available;
    sprites_available = sprites_available->next;
    free(to_free);

    static int num = 0;


    return (to_return);

}

//******************************************************************************
/**
 *   Make sure the sprite handler linked list knows a new sprite 
 *       became available. Next place to write should write over this area in OAM
 *       @param sprite_number the sprite number that has become available
 */ 

void Sprites::setSpriteAvailable(int sprite_number)
{

    SpritesAvailable* current; 
    //-------------------------------------------
    // Append reference to linked list
    //-------------------------------------------
    current = (SpritesAvailable*)malloc(sizeof(SpritesAvailable));
    current->sprite_number = (u8)sprite_number;
    //    Make all other sprites the children of this new one
    current->next = sprites_available;
    //    Set new sprite as head of list
    sprites_available = current;
    // Make sure GFX handler knows this space is free 
    //sprite_gfx_indexes[sprite_index] =  SPRITE_UNUSED;

}

//******************************************************************************
/**
 *    Check if sprite number is available: 0(n) time
 *       @param sprite_number the sprite number to look for
 *           @return if sprite number was found in available sprites list
 */

bool Sprites::isSpriteAvialable(int sprite_number)
{

    int i = 0;
    SpritesAvailable* current  = sprites_available;
    while(i < MAX_SPRITES && current != NULL)
    {

        if(sprite_number == (int)(current->sprite_number))
        {

            return (true);

        }
        current = current->next;
        i++;

    }
    return (false);

}

//******************************************************************************
/**
 *  Add graphics to GFX memory for a NEW SPRITE
 *   --offset (in bytes) of where to place sprite tiles into 
 *           GFX memory will be determined by a sprite handler
 *      @param tiles tiles gfx memory for a sprite
 *      @param size in bytes of the sprite to add to GFX memory
 *      @param 
 */

int Sprites::appendTileGFX(unsigned char* tiles, unsigned int size, 
        u8 sprite_index)
{
   
    int to_return = gfx_memory_index;
    setTileGFX(tiles,size,gfx_memory_index);
    //Debug::printSetup();
    //iprintf("\x1b[0;0H -atr[2]: 0x%08x",OAMCopy[sprite_index].attribute[2]);

    //setGFXMemoryIndexOAM(sprite_index, to_return);    
    gfx_memory_index += size;

    //Debug::printSetup();    
    //iprintf("\x1b[6;0H offset: 0x%08x",to_return);
    //	iprintf("\x1b[2;0H atr[0]: 0x%08x",OAMCopy[sprite_index].attribute[0]);
    //	iprintf("\x1b[3;0H atr[1]: 0x%08x",OAMCopy[sprite_index].attribute[1]);
    //iprintf("\x1b[4;0H atr[2]: 0x%08x",OAMCopy[sprite_index].attribute[2]);

    return to_return;

}

//******************************************************************************
/**
 *  Place OAM backup buffer in real OAM on Gameboy Adv
 */

void Sprites::copyObjToOAM()
{

    // Size of OAM is the size of one OAM record * number of sprites possible
    //			(There's one OAM record per sprite).
    static const int OAM_BYTES_SIZE = sizeof(OAM_Entry)*MAX_SPRITES;
    //dmaCopy((const void*)(OAMCopy), (void*)OAM, OAM_BYTES_SIZE);
    //DMA_Copy(3, (const void*)(OAMCopy), (void*)OAM, DMA32 | OAM_BYTES_SIZE>>2);
    dmaCopy32((const void*)(OAMCopy), (void*)OAM, OAM_BYTES_SIZE);

    //-------------------------------------------
    // Debuging info, keep for tests
    //-------------------------------------------
    //memcpy(OAM,OAMCopy, OAM_BYTES_SIZE);    
    //     Debug::printSetup();
    //     u16* OAMCopy16 = (u16*)OAMCopy;
    //     u16* OAM16 = (u16*)OAM;
    //     iprintf("\x1b[0;0H OAM byte size: %d",OAM_BYTES_SIZE);
    //     int test_index = 0;
    //     iprintf("\x1b[1;0H OAM[%d]=0x%04x%04x%04x%04x",test_index, OAM16[test_index],OAM16[test_index+1], 
    //        OAM16[test_index+2], OAM16[test_index+3]);
    //     iprintf("\x1b[3;0H OAMC[%d]]=0x%04x%04x%04x%04x",test_index, OAMCopy16[test_index],OAMCopy16[test_index+1], 
    //        OAMCopy16[test_index+2], OAMCopy16[test_index+3]);    
    //     iprintf("\x1b[4;0H REG_DISPCNT = %08x",REG_DISPCNT);
    //     static int i = 0;
    //     iprintf("\x1b[5;0H update: %d",i++);

}

//******************************************************************************
/**
 *   Set a DMA transfer to begin.
 *
 *   @param source the soruce for the data
 *   @param dest destination for the data to be transfered to
 *   @param count the count in bytes of data to be transfered
 *   @param mode the DMA mode to use for the transfer, can be
 *     #DMA_16NOW or #DMA_32NOW
 *
 */
inline void DMAFastCopy(void* source, void* dest, unsigned int count,
        unsigned int mode)
{

    if (mode == DMA_16NOW || mode == DMA_32NOW)
    {

        REG_DMA3SAD = (unsigned int)source;
        REG_DMA3DAD = (unsigned int)dest;
        REG_DMA3CNT = count | mode;

    }

}


