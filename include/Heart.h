#ifndef HEART_H_
#define HEART_H_

#include "Character.h"

extern const unsigned char heart_16x16_Tiles[256];
                                             
class Heart : public Character
{
	public:
		Heart();
		~Heart();
		Heart(int pallet_number2);
		
		void init(u8 pallet_number, int position_x, int position_y, 
					     int velocity_vector_x, int velocity_vector_y);
		virtual u8 getSpriteIndex(){return sprite_index; }
        virtual u8 getPalletNumber(){return pallet_number;}
		virtual void updateGraphic();
		// Debug variable
        int starting_y;
	protected:
		/** Whether pallet memory and tile mem were defined for Gummy characters */
        static int pallet_tile_mem_loaded;
        /** GFX memory index (how far into GFX memory are the tiles for this 
        	               character: if using same tile set for all gummys)*/
	   	static int gfx_memory_index;
};

#endif /*HEART_H_*/
