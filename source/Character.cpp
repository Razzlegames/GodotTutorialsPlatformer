#include "Character.h"

//*****************************************************************

Character::Character():
    collision_box(),
    position(0,0),
    velocity_vector(0,0),
    sprite_index(0),
    starting_y(0),
    in_motion(0),
    pallet_number(0),
    oam()
{

	init();

}

//*****************************************************************

Character::Character(unsigned char* tiles, int tiles_size,
        int tiles_loaded, int color_code, 
        int pallet_number2, int sprite_size_code)
{

	init(tiles, tiles_size, tiles_loaded,color_code, 
                pallet_number2, sprite_size_code, 50,70,0,0);
}

Character::~Character()
{

}

//*****************************************************************
/**
 *   Initialize all member vars to 0
 */

void Character::init()
{

    //collision_box.bottom_left = Vector2D(0,0);
    //collision_box.top_right = Vector2D(0,0);

    // The current position of the character*/
    position =  Vector2D(0,0);

    // The current velocity the character has */
    velocity_vector = Vector2D(0,0);

    // The sprite index the hardware had a reference to*/
    sprite_index =0;   	    

    // Debug cord
    starting_y =0;	 

    in_motion=0;     

    // This character's pallet number*/
    pallet_number=0;

}

//*****************************************************************
/**
 *  @param tiles tile memory for this char
 *  @param tiles_size size of tile mem (in bytes)
 *  @param tiles_loaded whether tiles were 
 *       already loaded for the child class
 *  @param pallet_number the index for the color pallet in memory
 *  @param sprite_size_code the size of sprite, 
 * 	Sprite_8x8...Sprite_64x64 [gba_sprites.h],
 *  @param position_x where sprite starts
 *  @param position_y where sprite starts
 *  @param velocity_vector_x beginning velocity
 *  @param velocity_vector_y beginning velocity
 */

void Character::init(unsigned char* tiles, int tiles_size, 
        int tiles_loaded, int color_code, 
        u8 pallet_number, int sprite_size_code, 
        int position_x, int position_y,
        int velocity_vector_x, int velocity_vector_y)
{

    // Debug cord
    starting_y = position_y;

    //this->state |= ON_GROUND;
    /*
    // Find out the shape of the sprite
    int shape = 0;
    if(sprite_size_code == Sprite_8x8 ||
    sprite_size_code == Sprite_16x16 ||
    sprite_size_code == Sprite_32x32 ||
    sprite_size_code == Sprite_64x64)
    {
    shape = SQUARE;
    }
    else if(sprite_size_code == Sprite_8x16 ||
    sprite_size_code == Sprite_16x32 ||
    sprite_size_code == Sprite_32x64)
    {
    shape = TALL;
    }

    else if(sprite_size_code == Sprite_16x8 ||
    sprite_size_code == Sprite_32x16 ||
    sprite_size_code == Sprite_64x32)
    {
    shape = WIDE;
    }

    //----------------------------------------------
    //		Display error condition (sprite shape unknown)
    //----------------------------------------------
    else
    {
    Debug::printSetup();
    iprintf("\x1b[0;0H Error sprite Shape undefined!");
    iprintf("\x1b[0;1H sprite_size_code: %d",sprite_size_code);
    while(1);
    }


    //----------------------------------------------
    // Find out size of sprite (attribute[1])
    //----------------------------------------------
    //	    
    //	            SIZE_8 	    SIZE_16     SIZE_32     SIZE_64
    //	    SQUARE  8x8  0000	16x16 0001	32x32 0010 	64x64 0011
    //	    TALL    8x16 0100 	8x32  0101	16x32 0110	32x64 0111
    //	    WIDE    16x8 1000	32x8  1001	32x16 1010	64x32 1011
    //	    
    int size = 0;
    if(sprite_size_code == Sprite_8x8 ||
    sprite_size_code == Sprite_8x16 ||
    sprite_size_code == Sprite_16x8)
    {
    size = ATTR1_SIZE_8;
    }

    else if(sprite_size_code == Sprite_16x16 ||
    sprite_size_code == Sprite_8x32 ||
    sprite_size_code == Sprite_32x8)
    {
    size = ATTR1_SIZE_16;
    }

    else if(sprite_size_code == Sprite_32x32 ||
    sprite_size_code == Sprite_16x32 ||
    sprite_size_code == Sprite_32x16)
    {
    size = ATTR1_SIZE_32;
    }

    else if(sprite_size_code == Sprite_64x64 ||
    sprite_size_code == Sprite_32x64 ||
    sprite_size_code == Sprite_64x32)
    {
    size = ATTR1_SIZE_64;
    }

    //----------------------------------------------
    //		Display error condition (sprite Size unknown)
    //----------------------------------------------
    else
    {
        Debug::printSetup();
        iprintf("\x1b[0;0H Error sprite Size undefined!");
        iprintf("\x1b[0;1H sprite_size_code: %d",sprite_size_code);
        while(1);
    }

    */

    this->pallet_number = pallet_number;
    this->position.x = position_x;
    this->position.y = position_y;
    this->velocity_vector.x = velocity_vector_x;
    this->velocity_vector.y = velocity_vector_y;  

    // Whether pallet memory and tile mem were defined 
    //  for Gummy characters 
    static int pallet_tile_mem_loaded = 0;

    this->sprite_index = 
        Sprites::createSprite(position_x, position_y, 
                sprite_size_code, color_code);

    Sprites::setSpritePosition(position.x, 
            position.y,sprite_index);

//    	Debug::printSetup();
//    	iprintf("\x1b[0;0H sprite_index: %08x",sprite_index);
//    	iprintf("\x1b[1;0H gfx_memory_index: %08x",gfx_memory_index);

}

