//
// File:   CrazyHero.h
// Author: kyle2
//
// Created on May 13, 2007, 11:24 AM
//
 
#ifndef _CrazyHero_H
#define	_CrazyHero_H

//#include "gfx/crazy_hero.raw.c"
//#include "gfx/crazy_hero.pal.c"
//#include "gfx/crazy_hero.map.c"
//#include "mygba.h"
#include <gba.h>
#include "Character.h"

/** The sprite size of this hero in pixels */
#define CRAZYHERO_OBJ_SIZE   OBJ_SIZE_32X32
/** The object mode of the hero sprite */
#define CRAZYHERO_OBJ_MODE  OBJ_MODE_NORMAL
/**  The length of one puzzle block in pixels */
#define ONE_BLOCK_LENGTH    3
/** Use this to plot a individual pixel in this sprite (for effects)*/
#define crazyHeroIndexPixel(x,y) x+y*32


/**
 *   Crazy alien guy
 */
class CrazyHero: public Character
{
    private:
        //--------------------------------------------
        //      Member attributes
        //--------------------------------------------
        /** The sprite index the hardware had a reference to*/
        u8 sprite_index;
        int position_x;
        int position_y; 
        int in_motion;
        /** Number of lights on the ship */
        #define NUMBER_OF_SHIP_LIGHTS   9        
        /** Ship light positions in sprite (relative to current 32X32)*/
        int* light_positions;
        //--------------------------------------------
        //  private Function prototypes 
        //--------------------------------------------
        void init();
    public: 
        //--------------------------------------------
        // Public member function prototypes
        //--------------------------------------------
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void setInMotion(int in_motion);        
        u8 getSpriteIndex();
        CrazyHero();
        ~CrazyHero();
        CrazyHero(u8 sprite_index, int position_x, int position_y, 
            int in_motion);
        CrazyHero(int position_x, int position_y, 
            int in_motion);
        void updateGraphic();
};

#endif	/* _CrazyHero_H */
