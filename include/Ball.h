#ifndef BALL_H_
#define BALL_H_

#include "Character.h"
#include "Gummy.h"

extern const unsigned char ball_blue_Tiles[256];

extern const unsigned char ball_Tiles[256];
const int BALL_PALLET_SIZE = sizeof(ball_blue_Tiles);
typedef enum BallColor_{BLUE_BALL, GREEN_BALL}BallColor;
class Ball : public Character
{
	public:
		Ball();
		Ball(int pallet_number2);
		virtual ~Ball();
		virtual void initCollisionBox();
		void init(u8 pallet_number, int position_x, int position_y, 
			     int velocity_vector_x, int velocity_vector_y);
		void init(unsigned char* ball_Tiles, u8 pallet_number, 
				 int position_x, int position_y, 
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

#endif /*BALL_H_*/
