#include "Heart.h"
#include "Gummy.h"

/** Whether pallet memory and tile mem were defined for Gummy characters */
int Heart::pallet_tile_mem_loaded =0;
/** GFX memory index (how far into GFX memory are the tiles for this 
	               character: if using same tile set for all gummys)*/
int Heart::gfx_memory_index =0;
//******************************************************************************
Heart::Heart(): Character()
{
	
}
//******************************************************************************
Heart::~Heart()
{
	
}
//******************************************************************************
Heart::Heart(int pallet_number2): Character(pallet_number2)
{
	init(pallet_number, 40,10, 0,0);
	
}
//******************************************************************************
void Heart::init(u8 pallet_number, int position_x, int position_y, 
			     int velocity_vector_x, int velocity_vector_y)
{
	// Debug cord
    starting_y = position_y;
    
    // Set up Collision Box (assume middle of box is current position of ball)
    Vector2D offset(0,5);
    collision_box.bottom_left = Vector2D(0,0)+offset;
    collision_box.top_right = Vector2D(7,10)+offset;
    
	 Character::init((unsigned char*)heart_16x16_Tiles,sizeof(heart_16x16_Tiles),
			 pallet_tile_mem_loaded,OBJ_256_COLOR,
		    	    		pallet_number, Sprite_16x16, 
		    	    		position_x, position_y,
		    	    		velocity_vector_x, velocity_vector_y);
	 //      Use if using same tiles for multiple gummys
    // Check if tile memory has already been initialized for this sprite type
    if(!pallet_tile_mem_loaded)
    {
    	gfx_memory_index = Sprites::appendTileGFX((unsigned char*)heart_16x16_Tiles, 
    			sizeof(heart_16x16_Tiles), sprite_index);
    	pallet_tile_mem_loaded = 1;
    }
    Sprites::setTileIndex(gfx_memory_index/64*4, sprite_index);
     
    Sprites::enableSprite(sprite_index);
//	     Debug::printSetup();	     
//	     iprintf("\x1b[0;0H sprite_number: %04x", sprite_index);
//	     iprintf("\x1b[1;0H OAMCopy[0].a[0]: %04x", Sprites::OAMCopy[0].attribute[0]);
//	     iprintf("\x1b[2;0H OAMCopy[0].a[1]: %04x", Sprites::OAMCopy[0].attribute[1]);
//	     iprintf("\x1b[3;0H OAMCopy[0].a[2]: %04x", Sprites::OAMCopy[0].attribute[2]);
//	     
//	     iprintf("\x1b[4;0H OAMCopy[1].a[0]: %04x", Sprites::OAMCopy[1].attribute[0]);
//	     iprintf("\x1b[5;0H OAMCopy[1].a[1]: %04x", Sprites::OAMCopy[1].attribute[1]);
//	     iprintf("\x1b[6;0H OAMCopy[1].a[2]: %04x", Sprites::OAMCopy[1].attribute[2]);
//	     
//	     iprintf("\x1b[7;0H OAMCopy[2].a[0]: %04x", Sprites::OAMCopy[2].attribute[0]);
//	     iprintf("\x1b[8;0H OAMCopy[2].a[1]: %04x", Sprites::OAMCopy[2].attribute[1]);
//	     iprintf("\x1b[9;0H OAMCopy[2].a[2]: %04x", Sprites::OAMCopy[2].attribute[2]);
}
//******************************************************************************
void Heart::updateGraphic()
{
	Character::updateGraphic();
}


