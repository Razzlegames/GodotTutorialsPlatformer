#include "CrazyHero.h"

#include "Sprites.h"
// These are now linked during compile process 
//      (better solution)
//#include "gfx/crazy_hero.raw.c"
//#include "gfx/crazy_hero.pal.c"
//#include "gfx/crazy_hero.map.c"

extern const unsigned char crazy_hero_Tiles[2048];
/**
*   Default contructor for the hero of the game
*/
CrazyHero::CrazyHero()
{
    
    this->position_x = 0;
    this->position_y = 0;
    this->in_motion = 0;
    init();
}
//******************************************************************************
CrazyHero::CrazyHero(int position_x, int position_y, 
    int in_motion)
{
    this->position_x = position_x;
    this->position_y = position_y;
    this->in_motion = in_motion; 
    init();
}
//****************************************************************************** 
CrazyHero::~CrazyHero()
{
    delete(this->light_positions);
}
//****************************************************************************** 

//******************************************************************************
/**
*   Do initial setup for this characer
*/
void CrazyHero::init()
{

    //this->sprite_index; 
    /* = ham_CreateObj(
                            (void*)crazy_hero_Tiles,        // A pointer to the tile data for this object
                            CRAZYHERO_OBJ_SIZE,                 // obj_shape & obj_size
                            CRAZYHERO_OBJ_MODE,                // obj_mode
                            1,                              // col_mode (1=256 colors)
                            0,                              // pal_no
                            0,                              // mosaic
                            0,                              // hflip
                            0,                              // vflip
                            0,                              // dbl_size
                            0,                              // prio
                            this->position_x,               // x position of sprite on screen
                            this->position_y                // y position of sprite on screen
                            );
                        */

}
//******************************************************************************
/**
*       
*/
CrazyHero::CrazyHero(u8 sprite_index, int position_x, int position_y, 
    int in_motion)
{      
    this->sprite_index = sprite_index;
    this->position_x = position_x;
    this->position_y = position_y;
    this->in_motion = in_motion;
}
//******************************************************************************
u8 CrazyHero::getSpriteIndex()
{
    return this->sprite_index;
}
//******************************************************************************
void CrazyHero::setInMotion(int in_motion)
{
    this->in_motion = in_motion;
}
//******************************************************************************
/**
*   Move the hero up one block space
*/
void CrazyHero::moveUp()
{
    // Remember subtraction = up since upper left is cordinate (0,0)
    this->position_y -= ONE_BLOCK_LENGTH;
    this->in_motion = 1;
}
//******************************************************************************
void CrazyHero::moveDown()
{
    // Remember subtraction = up since upper left is cordinate (0,0)
    this->position_y += ONE_BLOCK_LENGTH;    
    this->in_motion = 1;
}
//******************************************************************************
void CrazyHero::moveLeft()
{
   this->position_x -= ONE_BLOCK_LENGTH;     
   this->in_motion = 1;
}
//******************************************************************************
void CrazyHero::moveRight()
{
   this->position_x += ONE_BLOCK_LENGTH;     
   this->in_motion = 1;
}
//******************************************************************************
/**
*   Update the hero's animation graphics and location
*/
void CrazyHero::updateGraphic()
{
    //ham_SetObjXY(this->sprite_index, this->position_x, this->position_y);
    
    if(this->in_motion)
    {
        //ham_UpdateObjGfx(this->sprite_index,(void*)&crazy_hero_Tiles[32*32]);
        this->in_motion = 0;
    }
    else
    {
        //ham_UpdateObjGfx(this->sprite_index,(void*)&crazy_hero_Tiles[0]);
    }
}
//******************************************************************************



