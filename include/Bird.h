/* vim: set filetype=cpp.doxygen : */


/**
 *  Bird is a cool character to be used as hero and enemy alike.
 *       The charater is 32X32 pixels, therefore anywhere 
 *       this product appears,
 *       it is due to this size.
 */
#ifndef _Bird_H
#define	_Bird_H

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
#define BIRD_OBJ_SIZE   Sprite_64x32 //OBJ_SIZE_64x32
/// The object mode of the hero sprite 
#define BIRD_OBJ_MODE  ATT0_NORMAL

//------------------------------------------------
// Animation frames for character
//------------------------------------------------

/// Frame for Bird Turning Left from a right walk/run (indexes start at 0)
#define BIRD_TURN_LEFT_FRAME_NUMBER   8

/// Frame for Bird Standing Right (indexes start at 0)
#define BIRD_STAND_RIGHT_FRAME_NUMBER   0

/// Frame for Bird Standing Right (indexes start at 0)
#define BIRD_BLINK_FRAME_NUMBER 1

/// Frame for Bird walking right (indexes start at 0)
#define BIRD_WALK_RIGHT_FRAME_NUMBER   2

/// 2nd Frame for Bird walking right (indexes start at 0)
#define BIRD_WALK_RIGHT_FRAME2_NUMBER   \
    (BIRD_WALK_RIGHT_FRAME_NUMBER+1)

/// 3rd Frame for Bird walking right (indexes start at 0)
#define BIRD_WALK_RIGHT_FRAME3_NUMBER   \
    (BIRD_WALK_RIGHT_FRAME_NUMBER+2)

/// Frame for Bird when he dies 
#define BIRD_DIES_FRAME_NUMBER     5

/// Frame for when Bird is ducking 
#define BIRD_DUCKING_FRAME_NUMBER  3

///  Max animation speeds for the character 
#define BIRD_MAX_ANIMATION_SPEEDS    3

/// Frame for when Bird is jumping  
#define BIRD_JUMPING_FRAME_NUMBER 	6

/// Frame for when Bird is jumping  
#define BIRD_JUMPING_FRAME2_NUMBER  (BIRD_JUMPING_FRAME_NUMBER +1)

/// Total number of animation frames 
#define BIRD_NUMBER_OF_FRAMES  11   

/// The size (in bytes) of each animation frame 
#define BIRD_FRAME_SIZE    (32*64)

/// Number of gummy tiles per frame 
#define BIRD_TILES_PER_FRAME   byteIndexToTileIndex(BIRD_FRAME_SIZE)

/// Vector magnitude and direction (up) of the Gummies jump 
#define BIRD_JUMP_VECTOR    -15

/// The graphics tiles to use for this character 
extern const unsigned char 
bird_Tiles[BIRD_FRAME_SIZE*BIRD_NUMBER_OF_FRAMES];

//------------------------------------------------

/// Max speed that a gummy can be traveling 
///   in (+/-) X direction 
#define BIRD_MAX_X_VELOCITY    20

//typedef enum BirdState
//{
//
//    TURNING = 1<<0,
//    FLIPPED = 1<<1,
//    JUMPING = 1<<2,
//    ON_GROUND = 1<<3,
//    DUCKING = 1<<4
//
//};
//

//***********************************************************************
/**
 *   Represent the Bird character .
 */

class Bird: public Character
{

  protected:

    /// Frequency to Update graphics bit maps on 
    static const int GRAPHIC_UPDATE_FREQUENCY;

    //--------------------------------------------
    //      Member attributes
    //--------------------------------------------
    /// Whether or not to use separate GFX tiles for 
    ///       each gummy instance
    static int separate_gfx;

    int collision_flag;

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
    ///     Bird characters 
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

    Bird(u8 pallet_number);
    ~Bird();
    Bird(u8 pallet_number, int position_x, int position_y, 
            int velocity_vector_x, int velocity_vector_y);
    Bird(int position_x, int position_y,
            int in_motion);

    virtual void updateGraphic()
    {

        Character::updateGraphic();

    }

    void updateGraphic(Vector2D position);
    void jump(int pressed, u8 button_last_pushed);
    void updatePhysics();
    void stoppingX();   
    void updateGraphicOnGround();
    void updateGraphicJumping();
    void changeAnimationFrame(int frame);
    void flipRight();
    void flipLeft();

};

////-------------------------------------------------------------
//// Put all small member functions here and make inline
///   (now in Character.h)
////*************************************************************************
///**
//*   Enable sprite
//*/
//inline void Bird::enableSprite()
//{
//    Sprites::enableSprite(this->sprite_index);
//}
////***************************************************************
//inline u8 Bird::getSpriteIndex()
//{
//    return this->sprite_index;
//}
////***************************************************************
///**
//*   Set the character in motion
//*/
//inline void Bird::setInMotion(int in_motion)
//{
//    //this->in_motion = in_motion;
//}
//
////***************************************************************
//inline u8 Bird::getPalletNumber()
//{
//    return pallet_number;
//}
//****************************************************************
#endif	/* _Bird_H */

