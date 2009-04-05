/* vim: set filetype=cpp.doxygen : */


/**
 *  Gummy is a cool character to be used as hero and enemy alike.
 *       The charater is 32X32 pixels, therefore anywhere 
 *       this product appears,
 *       it is due to this size.
 */
#ifndef _Gummy_H
#define	_Gummy_H

#include "Sprites.h"
#include "world1_physics.h"
#include "music_constants.h"

#include "modules.h"
#include "samples.h"
#include "krawall.h"
#include "mtypes.h"
#include <gba.h>

//#include "mygba.h"
#include "Sprites.h"
#include "Character.h"

//  The raw sprite data 
extern OAM_Entry OAMCopy[128];
extern RotData* rotData;

/// The sprite size of this hero in pixels 
#define GUMMY_OBJ_SIZE   Sprite_32x32 //OBJ_SIZE_32X32
/// The object mode of the hero sprite 
#define GUMMY_OBJ_MODE  ATT0_NORMAL
///  The length of one puzzle block in pixels 
#define ONE_BLOCK_LENGTH    3

//------------------------------------------------
// Animation frames for character
//------------------------------------------------
/// The graphics tiles to use for this character 
extern const unsigned char gummy_Tiles[7168];


/// Frame for Gummy Turning Left from a right walk/run (indexes start at 0)
#define GUMMY_TURN_LEFT_FRAME_NUMBER   0
/// Frame for Gummy Standing Right (indexes start at 0)
#define GUMMY_STAND_RIGHT_FRAME_NUMBER   2
/// Frame for Gummy walking right (indexes start at 0)
#define GUMMY_WALK_RIGHT_FRAME_NUMBER   1
/// 2nd Frame for Gummy walking right (indexes start at 0)
#define GUMMY_WALK_RIGHT_FRAME2_NUMBER   3
/// Frame for Gummy when he dies 
#define GUMMY_DIES_FRAME_NUMBER     4
/// Frame for when Gummy is ducking 
#define GUMMY_DUCKING_FRAME_NUMBER  5
///  Max animation speeds for the character 
#define GUMMY_MAX_ANIMATION_SPEEDS    3
/// Frame for when Gummy is jumping  
#define GUMMY_JUMPING_FRAME_NUMBER 	6
/// Total number of animation frames 
#define GUMMY_NUMBER_OF_FRAMES  7   
/// The size (in pixels) of each animation frame 
#define GUMMY_FRAME_SIZE    ((sizeof(gummy_Tiles)/GUMMY_NUMBER_OF_FRAMES))
/// Number of gummy tiles per frame 
#define GUMMY_TILES_PER_FRAME   (GUMMY_FRAME_SIZE/(64)*2)
/// Vector magnitude and direction (up) of the Gummies jump 
#define GUMMY_JUMP_VECTOR    -28
//------------------------------------------------

/// Max speed that a gummy can be traveling 
///   in (+/-) X direction 
#define GUMMY_MAX_X_VELOCITY    20

typedef enum GummyState
{

    TURNING = 1<<0,
    FLIPPED = 1<<1,
    JUMPING = 1<<2,
    ON_GROUND = 1<<3,
    DUCKING = 1<<4

};


//****************************************************************************
/**
 *   Represent the Gummy character .
 */
class Gummy: public Character
{

  protected:

      //--------------------------------------------
      //      Member attributes
      //--------------------------------------------
      /// Whether or not to use separate GFX tiles for 
      ///       each gummy instance
      static int separate_gfx;

      int collision_flag;

      /// GFX memory index (how far into GFX memory are 
      /// the tiles for this character: if using 
      /// same tile set for all gummys)
      //int gfx_memory_index;

      /// The Object Attribute memory associated with this sprite 
      //OAM_Entry oam;
      /// This character's pallet number
      //u8 pallet_number;

      /// The sprite index the hardware had a reference to
      //u8 sprite_index;
      //  The current point on the screen the character 
      //        is occupying
      //int position_x;
      //int position_y;

      // The current velocity the character has
      //int velocity_vector_x;
      //int velocity_vector_y;

      /// If character is moving right
      int in_motion_right;

      /// If character is moving left
      int in_motion_left;

      // Debug variable
      int starting_y;

      /// If character is currently turning (used for different 
      ///       animation frame)
      int turning;

      /// Keep track of how many vblank interrupts have 
      ///     been thrown 
      ///     -Used in animation frame assignment 
      int vblank;

      /// If the graphic has been flipped left, turning, jumping
      int state;

      /// Whether pallet memory and tile mem were defined for 
      ///     Gummy characters 
      static int pallet_tile_mem_loaded;

      /// GFX memory index (how far into GFX memory are 
      ///     the tiles for this character: if using 
      ///     same tile set for all gummys)
      static int gfx_memory_index;

      //--------------------------------------------
      //  private Function prototypes
      //--------------------------------------------
      void init(u8 pallet_number, int position_x, 
              int position_y, int velocity_vector_x, 
              int velocity_vector_y, int in_motion_left, 
              int in_motion_right);

      virtual void updateWalkFrame();
      virtual void updateWalkRightFrame();
      virtual void updateWalkLeftFrame();

      /// The current animation frame of this character 
      int frame_number;

  public:

      //--------------------------------------------
      // Public member function prototypes
      //--------------------------------------------
      // Inherited
      //void enableSprite();

      //-------------------------------------------
      // Motion
      //-------------------------------------------
      void moveUp();
      void moveDown();        
      void moveLeft();
      void moveRight();        
      void moveLeftRunning();
      void moveRightRunning();

      void showCollision();
      int getOnGround(){ return state & ON_GROUND;};
      void setOnGround(){state &= ~JUMPING; state |= ON_GROUND;}
      void setOffGround(){state &= ~ON_GROUND;}

      //-------------------------------------------
      // Sounds
      //-------------------------------------------
      void playJumpSound();
      void playImpactSound();
      void playImpactSound(unsigned int volume);
      int getCollisionFlag(){return collision_flag;}

      // Inherited
      //void setInMotion(int in_motion);
      //u8 getPalletNumber();
      //u8 getSpriteIndex();

      Gummy(u8 pallet_number);
      ~Gummy();
      Gummy(u8 pallet_number, int position_x, int position_y, 
              int velocity_vector_x, int velocity_vector_y);
      Gummy(int position_x, int position_y,
              int in_motion);

      void updateGraphic(Vector2D position);
      void jump(int pressed, u8 button_last_pushed);
      void updatePhysics();
      void stoppingX();   
      void updateGraphicOnGround();
      void changeAnimationFrame(int frame);

};

////-------------------------------------------------------------
//// Put all small member functions here and make inline
///   (now in Character.h)
////******************************************************************************
///**
//*   Enable sprite
//*/
//inline void Gummy::enableSprite()
//{
//    Sprites::enableSprite(this->sprite_index);
//}
////***************************************************************
//inline u8 Gummy::getSpriteIndex()
//{
//    return this->sprite_index;
//}
////***************************************************************
///**
//*   Set the character in motion
//*/
//inline void Gummy::setInMotion(int in_motion)
//{
//    //this->in_motion = in_motion;
//}
//
////***************************************************************
//inline u8 Gummy::getPalletNumber()
//{
//    return pallet_number;
//}
//****************************************************************
#endif	/* _Gummy_H */

