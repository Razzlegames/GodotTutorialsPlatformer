///// 
///// File:   Sprites.h
///// Author: kyle2
/////
///// Created on June 25, 2007, 9:21 PM
/////
///
///        SIZE_8 	SIZE_16 SIZE_32 SIZE_64
///SQUARE  8x8 	16x16 	32x32 	64x64
///TALL    8x16 	8x32 	16x32 	32x64
///WIDE    16x8 	32x8 	32x16 	64x32
///
///---------------------------------------------------
///OAM Memory notes (according to pern):
///---------------------------------------------------
///Attribute[0]
///bits 	F 	E 	D 	C 	B 	A 	9 	8 	7 	6 	5 	4 	3 	2 	1 	0
///        |  Shape|	C 	M 	Mode 	SD 	R 	|       Y Coordinate
///
///Bits 0-7 form an 8bit signed integer (range = [-128, 127]) denoting the top of your sprite. 
///    ANDing your sprite's top with 255 to wrap around the screen. For example, 
///    say that the top is int y = -1 (one pixel above the screen). 
///    In hex, this is 0xFFFFFFFF; -1 & 255 = 0xff, which is indeed -1 for signed 8bit integers.
///Bit 8 is the rotation scaling flag. If set it will draw the sprite with the 
///    scaling/rotation parameters specified.
///Bit 9 is something called the size double flag and I will talk about this 
///    when I describe sprite rotation. One interesting effect of the SD flag 
///    is that if it is set, but the rotation flag is not, then that sprite will 
///    not be displayed. This is how we will turn off all of the unused sprites 
///    and why this flag is sometimes referred to as the TURN_OFF flag.
///Bits A-B are the mode flags and deal with alpha blending. I will talk about that
///    more in chapter 9.
///Bit C is the mosaic flag. When set the sprite will have the mosaic value 
///    applied to it. This topic is also saved for day 9.
///Bit D is the color mode. If set it defines the sprite as 256-colors. If 
///    cleared it uses a 16-color palette.
///Bit E-F is the object's shape and will be described in more detail when 
///    we actually draw our first sprite.
///
///Attribute[1] 
///bits 	F 	E 	D 	C 	B 	A 	9 	8 	7 	6 	5 	4 	3 	2 	1 	0
///        |   Size|       VF      HF     |RotData index   |       X Coordinate [9bits]
///
///Bits 0-8 form the left of the sprite. Similar to the top, these 9 bits form a signed 
///    integer, with the range [-256, 255]. This time, AND with 511 for correct wrapping.
///Bits 9-13 serve a dual purpose. If the rotation scaling flag is set in attribute[0]
///    then they are the 5-bit index (0-31) into the rotData array and define which 
///    set of rot/scaling parameters are going to be used with that sprite. 
///    If the rotation scaling flag is not set then bits 9-11 are not used.
///Bit 12 is the horizontal flip flag (the sprite will be flipped along the y axis) 
///    and bit 13 is the vertical flip flag (x axis). These attributes are not 
///    used when the rotation flag is set in attribute[0].
///Bit 14-15 is the size and I will give you a nice little table that explains
///    the use of this flag and the shape
///
///Attribute[2]
///
///bits 	F 	E 	D 	C 	B 	A 	9 	8 	7 	6 	5 	4 	3 	2 	1 	0
/// 	Palette number                 |Priority       |Character Name
///
///Bit 0-9 is the index into sprite character memory of the first 8x8 tile of the 
///    sprite (to fully understand this flag wait until I describe the second area of sprite memory).
///Bit 10-11 is the priority. As with backgrounds sprites can be assigned a priority
///    of 0-3. Higher numbered sprites are drawn first, meaning that a sprite of 
///    priority 0 will be drawn over the top of a sprite with priority of 3. 
///    Also, a sprite priority is always higher than that of the corresponding 
///    background priority meaning that if both a sprite and a background have 
///    the same priority then the sprite will be drawn on top. One more thing: 
///    for sprites with the same priority then sprites with the lowest OAM number 
///    are drawn on top.
///Bits 12-15 are the palette number. If your sprite is a 16-color sprite then this 
///    value will determine which of the 16 16-color palettes are used. If it is a
///    256-color sprite then these bits are ignored.
///


#ifndef _Sprites_H
#define	_Sprites_H
#include "gba_data_types.h"
#include "bit_setting.h"
#include "registers.h"
#include <gba.h>
#include <stdlib.h>
//#include <gba_dma.h>
//#include <gba_sprites.h>
//#include <gba_video.h>
#include <string.h>
#include "Debug.h"
#include "Vector2D.h"

//sprite defines
//Attribute0 stuff

//#define ROTATION_FLAG      BIT8
//#define SIZE_DOUBLE        BIT9
//#define SPRITE_OFF         BIT9
//#define MODE_NORMAL        0
//#define MODE_TRANSPARENT   BIT(0xA)
//#define MODE_WINDOWED      BIT(0xB)
//#define MOSAIC             BIT(0xC)
//#define COLOR_16           0
//#define COLOR_256          BIT(0xD)
////#define SQUARE             0
////#define TALL               BIT(0xF)
////#define WIDE               BIT(0xE)
//
////Attribute1 stuff
//#define ROTDATA(n)         ((n) << 9)
//#define HORIZONTAL_FLIP    BIT(0xC)
//#define VERTICAL_FLIP      BIT(0xD)
//#define SIZE_8             0
//#define SIZE_16            BIT(0xE)
//#define SIZE_32            BIT(0xF)
//#define SIZE_64            BIT(0xF) | BIT(0xE)

//attribute2 stuff
#define PRIORITY(n)        ((n) << 10)
#define PALETTE(n)         ((n) << 12)


#define spriteTypeToSize(n) ((n&0x0003)<<14)
#define spriteTypeToShape(n) ((n&0x000C)<<12)

#define MAX_SPRITES     128
#define TILE_ATTRIBUTE_MASK     0x3FF
#define byteIndexToTileIndex(n) (n/32)

//#include "mygba.h"

/** This is the OAM memory as it is laid out in the GBA */
class OAM_Entry
{

  public:
#define ATTR_SIZE 3

    u16 attribute[ATTR_SIZE];
    u16 filler;

    OAM_Entry():
        filler(0)
    {

        for(int i = 0; i < ATTR_SIZE; i++)
        {

            attribute[i] = 0;

        }

    }

#undef ATTR_SIZE

};

/** Rotation data that overlaps OAM 
  (for scaling & rotating sprites)*/
typedef struct
{

    u16 filler1[3];
    u16 pa;
    u16 filler2[3];
    u16 pb;
    u16 filler3[3];
    u16 pc;
    u16 filler4[3];
    u16 pd;

}RotData;

/** If no sprites are available to the system */
#define NO_SPRITES_LEFT     0xFF
/** Used to indicate when a sprite is not being used
  Helps to figure out where GFX tile data blocks are available */
#define SPRITE_UNUSED   0xFF

//-------------------------------------------------------
/// For keeping track of what sprite numbers are available to the system 
//-------------------------------------------------------
typedef struct SpritesAvailable_ 
{

    u8 sprite_number;
    struct SpritesAvailable_* next;

}SpritesAvailable;

//-------------------------------------------------------
/// A Memory manager linked list of GFX memory currently being occupied
//-------------------------------------------------------
typedef struct SpriteGFX_
{

    /// Offset into GFX memory this sprite begins at*/
    u16 begin_index;

    /// Size of GFX memory this refers to 
    u16  size;

    /// pointer to the next contiguous block of memory being 
    ///         used for GFX 
    struct SpriteGFX_* next;

}SpriteGFX;

const int GFX_MEMORY_SIZE   = 32*(2^10);

//************************************************************************
/**
*  Used to control all apsects of sprites in this game. Including 
*       memory access availability linked list
*/

class Sprites
{

  public:
      /// the current GFX memory a new sprite should be loaded into
      static int gfx_memory_index;

      __attribute__((aligned(4))) static OAM_Entry OAMCopy[MAX_SPRITES];
      static RotData* rotData;

      /// Current index into sprite pallet memory that should be 
      /// written to  (not needed in 256 color mode)
      static int sprite_pallet_index;

      /// Create a linked list of sprite numbers that are available */
      __attribute__((aligned(4))) 
          static SpritesAvailable* sprites_available;

      /// Create linked list to GFX memory being used */
      __attribute__((aligned(4))) static SpriteGFX* sprite_gfx;

      //-------------------------------------------
      //   GFX Prototypes
      //-------------------------------------------
      static void setTileGFX(unsigned char* tiles, unsigned int size, 
              unsigned int offset);
      static bool setGFXMemoryUsed(int begin_index, unsigned int size);
      static bool checkGFXBounds(int begin_index, int size);
      static bool freeGFXBlock(int begin_index);
      static void setGFXMemoryIndexOAM(int sprite_number, int offset);
      void updateTileGFX(unsigned char* tiles, unsigned int size,
              int sprite_gfx_index);

      //-------------------------------------------
      //   Sprite Prototypes
      //-------------------------------------------
      static void setSpriteSize(const int size, int sprite_number);
      static void setSpriteShape(const int shape, int sprite_number);
      static void setSpriteColorModeAndShape(const int shape, 
              const int color, int sprite_number);

      static void enableSprite(int sprite_number);
      static void disableAllSprites();
      static bool isSpriteAvialable(int sprite_number);
      static void initSprites();
      static void initSpritesAvailable();
      static u8 getNextAvailableSprite();
      static void disableSprite(int sprite_number);
      static void setSpriteAvailable(int sprite_number);
      static void setSpritePosition(int x, int y, int sprite_number);
      static void setSpritePosition(Vector2D point, int sprite_number);
      static void getSpritePosition(Vector2D* point, int sprite_number);
      static int getSpriteXCoord(int sprite_number);
      static int getSpriteYCoord(int sprite_number);
      static void setSpriteXCoord(int x, int sprite_number);
      static void setSpriteYCoord(int y, int sprite_number);
      static void flipSpriteVertical(int index);
      static void flipSpriteHorizontal(int index);
      static void setTileIndex(int index, int sprite_number);
      static int getTileIndex(int sprite_number);
      static void copyObjToOAM();
      static int addTileGFX(unsigned char* tiles, unsigned int size, 
              u8 sprite_index);

      static int appendTileGFX(unsigned char* tiles, unsigned int size, 
              u8 sprite_index);

      static void addPalletData(unsigned char* pallet, int size);

      static u8 createSprite(int x, int y, 
              int sprite_size_code, int color);

      static void DMAFastCopy(void* source, void* dest, 
              unsigned int count, unsigned int mode);

      static void displaySpriteInfo(int sprite_number);

};

//************************************************************************
/**
 *   Check to see if a GFX memory insert is out of bounds (higher than 32kb 
 *    allowed)
 *       @param begin_index address GFX will be placed in 
 *           (relative to GFX starting address)
 *       @param size size of GFX block to place in system
 */

inline bool Sprites::checkGFXBounds(int begin_index, int size)
{

    if(begin_index+size >= GFX_MEMORY_SIZE)
    {

        Debug::printSetup();
        iprintf("\x1b[0;0H MEMORY MANAGEMENT ERROR!");
        iprintf("\x1b[0;1H ATTEMPT TO INSERT GFX at: %d +GFX",
                begin_index+size);
        iprintf("\x1b[0;2H Max GFX size is: %d - 1", GFX_MEMORY_SIZE);

        return false;

    }
    return true;

}

//************************************************************************
/**
 *
 *   Enable a sprite by clearing the "size double flag" in it's OAM
 *
 */

inline void Sprites::enableSprite(int sprite_number)
{

    // ATTR0_DISABLED represents the bit we want to clear. So flip the bits and AND it
    OAMCopy[sprite_number].attribute[0] &= ~ATTR0_DISABLED;

    //    Debug::printSetup();
    //    //iprintf("\x1b[0;0H TEst!");
    //        iprintf("\x1b[0;0H sprite_number: %04x", sprite_number);
    //        iprintf("\x1b[1;0H OAMCopy[0].a[0]: %04x", OAMCopy[0].attribute[0]);
    //        iprintf("\x1b[2;0H OAMCopy[0].a[1]: %04x", OAMCopy[0].attribute[1]);
    //        iprintf("\x1b[3;0H OAMCopy[0].a[2]: %04x", OAMCopy[0].attribute[2]);
    //        
    //        iprintf("\x1b[4;0H OAMCopy[1].a[0]: %04x", OAMCopy[1].attribute[0]);
    //        iprintf("\x1b[5;0H OAMCopy[1].a[1]: %04x", OAMCopy[1].attribute[1]);
    //        iprintf("\x1b[6;0H OAMCopy[1].a[2]: %04x", OAMCopy[1].attribute[2]);
    //        
    //        iprintf("\x1b[7;0H OAMCopy[2].a[0]: %04x", OAMCopy[2].attribute[0]);
    //        iprintf("\x1b[8;0H OAMCopy[2].a[1]: %04x", OAMCopy[2].attribute[1]);
    //        iprintf("\x1b[9;0H OAMCopy[2].a[2]: %04x", OAMCopy[2].attribute[2]);
    /*
       u16* OAMCopy16 = (u16*)OAMCopy;
       u16* OAM16 = (u16*)OAM;
       int test_index = 0;
       iprintf("\x1b[0;0H AND MASK: 0x%02x",(u16)~ATTR0_DISABLED);
       iprintf("\x1b[1;0H *OAM[%d]={0x%04x%04x%04x..}",test_index, OAM16[test_index],
       OAM16[test_index+1],OAM16[test_index+2]);
       iprintf("\x1b[3;0H *OAMCopy[%d]]={0x%04x%04x%04x..}",test_index, OAMCopy16[test_index],
       OAMCopy16[test_index+1], OAMCopy16[test_index+2]);
       iprintf("\x1b[0;0H AND MASK: 0x%02x",(u16)~ATTR0_DISABLED);
     */

}

//************************************************************************
/**
 *      Disable the showing of a sprite by setting the "size double flag"
 */

inline void Sprites::disableSprite(int sprite_number)
{

    OAMCopy[sprite_number].attribute[0] |= ATTR0_DISABLED;

}

//************************************************************************
/**
 * Attribute[2]

 bits 	F 	E 	D 	C 	B 	A 	9 	8 	7 	6 	5 	4 	3 	2 	1 	0
 Palette number                 |Priority       |Character Name

 Bit 0-9 is the index into sprite character memory of the first 8x8 tile of the 
 sprite (to fully understand this flag wait until I describe the second area of sprite memory).
 */

inline void Sprites::setGFXMemoryIndexOAM(int sprite_number, int offset)
{

    const unsigned int GFX_MASK = 0x03FF;

    Debug::printSetup();
    iprintf("\x1b[0;0H offset: 0x%08x",offset);
    offset = (offset/(8*8)*2)&GFX_MASK;
    OAMCopy[sprite_number].attribute[2] &= ~GFX_MASK;

    iprintf("\x1b[1;0H atr[2]: 0x%08x",
            OAMCopy[sprite_number].attribute[2]);

    OAMCopy[sprite_number].attribute[2] |= offset;
    iprintf("\x1b[2;0H offset: 0x%08x",offset);
    iprintf("\x1b[3;0H atr[2]: 0x%08x",
            OAMCopy[sprite_number].attribute[2]);

}

//************************************************************************
/**
 *  Add graphics to GFX memory
 *      @param tiles tiles gfx memory for a sprite
 *      @param size in bytes of the sprite to add to GFX memory
 *      @param offset offset (in bytes) of where to place sprite tiles into 
 *           GFX memory
 */

inline void Sprites::setTileGFX(unsigned char* tiles, unsigned int size, 
        unsigned int offset)
{

    //    Debug::printSetup();
    //    iprintf("\x1b[0;0H size to send: %d",size);
    dmaCopy(tiles, (unsigned char*)(SPRITE_GFX+offset), size);
    //memcpy((unsigned char*)SPRITE_GFX, tiles, size);

    //Debug::printSetup();    
    //iprintf("\x1b[0;0H offset: 0x%08x",offset);


    //iprintf("\x1b[1;0H ~offset: 0x%08x",~offset);

    //iprintf("\x1b[0;0H GFX_MEM: 0x%x",SPRITE_GFX+offset);

    //iprintf("\x1b[1;0H tiles:0x%x size:%d",tiles,size);
    //iprintf("\x1b[2;0H *SPRITE_GFX[%d] = {0x%04x%04x...}",320, *(SPRITE_GFX+320), *(SPRITE_GFX+321));

    //iprintf("\x1b[3;0H *tiles[%d] = {0x%02x%02x%02x%02x...}",320, tiles[640],tiles[641], tiles[642], tiles[643]);

}

//************************************************************************
/**
 *   Set the sprite's color mode (4bpp, 8bpp) and shape
 */

inline void Sprites::setSpriteColorModeAndShape(const int shape, 
        const int color_mode, int sprite_number)
{

    OAMCopy[sprite_number].attribute[0] |= OBJ_SHAPE(shape) | 
        color_mode;

}

//************************************************************************
/**
 *   Set a sprite's shape
 *       @param shape the shape code for the sprite SQUARE, WIDE, TALL
 */

inline void Sprites::setSpriteShape(const int shape, int sprite_number)
{

    OAMCopy[sprite_number].attribute[0] |= OBJ_SHAPE(shape);
    //    Debug::printSetup();
    //    iprintf("\x1b[1;0H shape number  %d ", OBJ_SHAPE(shape));

}

//************************************************************************
/**
 *       Set the sprites size code 
 */

inline void Sprites::setSpriteSize(const int size, int sprite_number)
{

    OAMCopy[sprite_number].attribute[1] |= size;
    //    Debug::printSetup();
    //    iprintf("\x1b[2;0H sprite size  %x ", OBJ_SIZE(size));

}

//************************************************************************
/**
 *   Set the sprite's position on the screen
 *       @param x x-cord
 *       @param y y-cord
 *       @param sprite_number the unique number given to the sprite 0-127
 */

inline void Sprites::setSpritePosition(int x, int y, int sprite_number)
{

    // Set sprite's y cordinate (8 bits of data)
    setSpriteYCoord(y, sprite_number);

    // Set sprite's x cordinate (actually 9 bits of data!) 
    setSpriteXCoord(x, sprite_number);  

    //Debug::printSetup();
    //iprintf("\x1b[0;0H sprite_position {%d,%d} ", x,y);

}

//************************************************************************
/**
 *   Set a sprites position given only it's oam memory
 *       @param point cords to set sprite on screen
 *       @param sprite_number sprite number
 */

inline void Sprites::setSpritePosition(Vector2D point, int sprite_number)
{

    // Set sprite's y cordinate (8 bits of data)
    setSpriteYCoord(point.y, sprite_number);

    // Set sprite's x cordinate (actually 9 bits of data!) 
    setSpriteXCoord(point.x, sprite_number);  

}

//************************************************************************
/**
 *   Set a sprites Y cord
 */  

inline void Sprites::setSpriteYCoord(int y, int sprite_number)
{

    // Set sprite's y cordinate (8 bits of data)
    OAMCopy[sprite_number].attribute[0] &= 0xFF00;
    OAMCopy[sprite_number].attribute[0] |= (0x00FF)&y;

}

//************************************************************************
/**
 *   Set a sprites Y cord
 */  

inline void Sprites::setSpriteXCoord(int x, int sprite_number)
{

    // Set sprite's x cordinate (actually 9 bits of data!) 
    OAMCopy[sprite_number].attribute[1] &= 0xFE00;
    OAMCopy[sprite_number].attribute[1] |= (0x01FF)&x; 

}

//************************************************************************
/**
 *   Return a sprite's position, based on it's OAM
 *       @param point point on screen to return
 *       @param oam Object attribute memory for a sprite 
 *          (NOT THE ARRAY of ALL OAM!)
 */

inline void Sprites::getSpritePosition(Vector2D* point, int sprite_number)
{

    // Get sprite's y cordinate (8 bits of data)
    point->x = (u16)getSpriteXCoord(sprite_number);
    point->y = (u16)getSpriteYCoord(sprite_number);

}

//************************************************************************
/**
 *   Get a sprites y cordinate on the screen
 *       @param oam Object attribute memory for a sprite 
 */

inline int Sprites::getSpriteYCoord(int sprite_number)
{

    // Get sprite's x cordinate (actually 9 bits of data!) 
    return (OAMCopy[sprite_number].attribute[1] & (0x01FF));

}

//************************************************************************
/**
 *   Get a sprites x cordinate on the screen
 *       @param oam Object attribute memory for a sprite 
 */

inline int Sprites::getSpriteXCoord(int sprite_number)
{

    // Get sprite's x cordinate (actually 9 bits of data!) 
    return OAMCopy[sprite_number].attribute[0] & (0x00FF);

}

//************************************************************************
/**
 *  Flip a sprite picture vertically
 *       @param index sprite number to change
 */

inline void Sprites::flipSpriteVertical(int index)
{

    OAMCopy[index].attribute[1] ^= OBJ_VFLIP;   

}

//************************************************************************
/**
 *  Flip a sprite picture horizontaly
 *       @param index sprite number to change
 */ 

inline void Sprites::flipSpriteHorizontal(int index)
{

    OAMCopy[index].attribute[1] ^= OBJ_HFLIP;   

}

//************************************************************************
/**
 *  Get tile set index
 */ 

inline int Sprites::getTileIndex(int sprite_number)
{

    return OBJ_CHAR(OAMCopy[sprite_number].attribute[2]);

}

//************************************************************************
/**
 *    Set the sprites tile set it is referencing
 *       @param index sprite index to use for tiles
 *       @param sprite_number sprite number to change
 */

inline void Sprites::setTileIndex(int index, int sprite_number)
{

    OAMCopy[sprite_number].attribute[2] &= ~TILE_ATTRIBUTE_MASK;
    OAMCopy[sprite_number].attribute[2] |= TILE_ATTRIBUTE_MASK&index;

}

//************************************************************************
/**
 *   Display sprite info for 2 contigous sprites
 */

inline void Sprites::displaySpriteInfo(int sprite_number)
{

    Debug::printSetup();
    iprintf("\x1b[0;0H OAM[%d].att[0]: 0x%04x",sprite_number,
            OAMCopy[sprite_number].attribute[0]);
    iprintf("\x1b[1;0H OAM[%d].att[1]: 0x%04x",sprite_number,
            OAMCopy[sprite_number].attribute[1]);
    iprintf("\x1b[2;0H OAM[%d].att[2]: 0x%04x",sprite_number,
            OAMCopy[sprite_number].attribute[2]);
    sprite_number++;

    iprintf("\x1b[3;0H OAM[%d].att[0]: 0x%04x",sprite_number,
            OAMCopy[sprite_number].attribute[0]);
    iprintf("\x1b[4;0H OAM[%d].att[1]: 0x%04x",sprite_number,
            OAMCopy[sprite_number].attribute[1]);
    iprintf("\x1b[5;0H OAM[%d].att[2]: 0x%04x",sprite_number,
            OAMCopy[sprite_number].attribute[2]);

}

#endif	/* _Sprites_H */

