/* vim: set filetype=cpp.doxygen : */

#include "BallRed.h"

/** Whether pallet memory and tile mem were defined for Gummy characters */
int BallRed::pallet_tile_mem_loaded = 0;
/** GFX memory index (how far into GFX memory are the tiles for this 
	               character: if using same tile set for all gummys)*/
int BallRed::gfx_memory_index = 0;

BallRed::BallRed(int pallet_number2): Ball(pallet_number2)
{
	init(pallet_number2, 50,70,0,0);
}
//******************************************************************************
void BallRed::init(u8 pallet_number, 
		 int position_x, int position_y, 
	     int velocity_vector_x, int velocity_vector_y)
{

	// Debug cord
    starting_y = position_y;
    //this->state |= ON_GROUND;
    
    // Set up Collision Box (assume middle of box is current position of ball)
    Ball::initCollisionBox();           
    
	Character::init((unsigned char*)ball_red_Tiles,BALL_TILE_SIZE,
			pallet_tile_mem_loaded, OBJ_256_COLOR,
	    		pallet_number, Sprite_16x16, 
	    		position_x, position_y,
	    		velocity_vector_x, velocity_vector_y);
    
    //      Use if using same tiles for multiple gummys
    // Check if tile memory has already been initialized for this sprite type
    if(!pallet_tile_mem_loaded)
    {
    	gfx_memory_index = Sprites::appendTileGFX((unsigned char*)ball_red_Tiles, 
    			BALL_TILE_SIZE, sprite_index);
    	pallet_tile_mem_loaded = 1;
    }
    Sprites::setTileIndex(gfx_memory_index/64*4, sprite_index);
    
    Sprites::enableSprite(sprite_index);
    //Debug::printSetup();
	    		
		//iprintf("\x1b[3;0H current.p: %d,%d",position.x,position.y);
//        Debug::printSetup();
//        iprintf("\x1b[0;0H GFXMemory: %08x",ball_Tiles);
//        iprintf("\x1b[1;0H gfx_memory_index: %08x",gfx_memory_index);
}
