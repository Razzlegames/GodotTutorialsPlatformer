#include "Bird.h"

#define STARTING_Y      120

//      Define your statics
int Bird::separate_gfx;

/// Whether pallet memory and tile mem were defined 
///     for Bird characters 
int Bird::pallet_tile_mem_loaded = 0;

/// GFX memory byte index (how far into GFX memory are 
///     the tiles for this character(in bytes): if using same tile 
///     set for all Birds)
int Bird::gfx_memory_index =0;

/// Frequency to Update graphics bit maps on 
const int Bird::GRAPHIC_UPDATE_FREQUENCY = 3;

//*****************************************************************
/**
 *   Default contructor for the hero of the game
 */
Bird::Bird(u8 pallet_number) : Character()
{

    starting_y = STARTING_Y;
    init(pallet_number, 50,starting_y,0,0, 0, 0);

}

//*****************************************************************

Bird::Bird(u8 pallet_number, int position_x, int position_y, 
        int velocity_vector_x, int velocity_vector_y): Character()
{

    starting_y = position_y;
    init(pallet_number, position_x, position_y, 
            velocity_vector_x, velocity_vector_y,0,0);

}

//**************************************************************** 
Bird::~Bird()
{

}

//*****************************************************************
/**
 *   Do initial setup for this characer
 */

void Bird::init(u8 pallet_number, int position_x, 
        int position_y, int velocity_vector_x, 
        int velocity_vector_y, int in_motion_right,
        int in_motion_left)
{   

    Bird::separate_gfx = true;

    // Debug cord
    starting_y = position_y;

    this->state |= ON_GROUND;
    this->frame_number = BIRD_STAND_RIGHT_FRAME_NUMBER;
    this->turning = 0;
    this->pallet_number = pallet_number;
    this->position.x = position_x;
    this->position.y = position_y;
    //position = Vector2D(10,10);
    this->velocity_vector.x = velocity_vector_x;
    this->velocity_vector.y = velocity_vector_y;
    this->in_motion_left = in_motion_left;
    this->in_motion_right = in_motion_right;   
    this->vblank = 0;    

    // Set up the Collision Box
    //
    // bottom_left
    // |_____________|
    // |             |
    // |             |
    // |             |
    // |_____________|
    //              top_right
    //
    collision_box.bottom_left = Vector2D(14,0);
    collision_box.top_right = Vector2D(64,31);
    collision_flag = 0;

    // Whether pallet memory and tile mem were defined for 
    //  Bird characters 
    static int pallet_tile_mem_loaded = 0;

    this->sprite_index = Sprites::createSprite(position.x, 
            position_y, Sprite_64x32, OBJ_256_COLOR);

    //      Use if using same tiles for multiple Birds
    // Check if tile memory has already been initialized 
    //  for this sprite type
    //if(!pallet_tile_mem_loaded)
    //{

        this->gfx_memory_index = Sprites::appendTileGFX(
                (unsigned char*)bird_Tiles+BIRD_FRAME_SIZE*1, 
                BIRD_FRAME_SIZE, sprite_index);

        int bird_tile_index = 
                byteIndexToTileIndex(gfx_memory_index)*2;

        Sprites::setTileIndex(
                // multiply by two if using 256bit pallet
                bird_tile_index, sprite_index);
        pallet_tile_mem_loaded = 1;

        //}

    Sprites::enableSprite(sprite_index);

    //Debug::printSetup();
    //iprintf("\x1b[0;0H Bird gfx_mem_index: %08x",gfx_memory_index);
    //iprintf("\x1b[1;0H Bird sprite_num: %08x",sprite_index);
    //iprintf("\x1b[2;0H Bird Frame size: %08x",BIRD_FRAME_SIZE);
    //iprintf("\x1b[3;0H Bird tile index: %08x",
    //bird_tile_index);

}

//*****************************************************************
/**
 */

void Bird::showCollision()
{

    collision_flag = 1;
    //state &= ~JUMPING; 
    // Show that the char is not on ground
    //state |= ON_GROUND;

}


//*****************************************************************
/**
 *   If the character is not already in motion (in y direction), 
 *   apply a jump
 *       @param pressed if jump button was being pressed
 *       @param button_last_pushed the button was being 
 *       pushed during the last frame
 */

void Bird::jump(int pressed, u8 button_last_pushed)
{

    if(pressed && button_last_pushed == 0 && 
            velocity_vector.y <= 4 
            /*&& position.y == starting_y*/)
    {

        state |= JUMPING; 

        // Show that the char is not on ground
        state &= ~ON_GROUND;

        // Make sure jump sizes will also depend on how 
        //   fast we are traveling :)
        //   And off the first bit, as to make this unsigned 
        //        (so velocity in either x direction is considered)
        velocity_vector.y = BIRD_JUMP_VECTOR;


        // Here is where the jump size depends on speed of character
        velocity_vector.y -= abs(velocity_vector.x/2);

        // Jump sound effect
        playJumpSound();

    }

    // For not being pressed
    else if(!pressed && button_last_pushed == 1 && 
            velocity_vector.y < 0)
    {

        velocity_vector.y = 0;

    }

    // Apply a fly action if already in the air
    else if(pressed && button_last_pushed == 0)
    {

        state |= JUMPING; 

        // Show that the char is not on ground
        state &= ~ON_GROUND;

        // Make sure jump sizes will also depend on how 
        //   fast we are traveling :)
        //   And off the first bit, as to make this unsigned 
        //        (so velocity in either x direction is considered)
        velocity_vector.y = BIRD_JUMP_VECTOR>>2;


    }

}


//*****************************************************************
/**
 *   Move the hero up one block space
 *   (Remember subtraction = up since upper left is cordinate (0,0))
 */

void Bird::moveUp()
{

    // Remember subtraction = up since upper left is cordinate (0,0)
    //position_y -= ONE_BLOCK_LENGTH;

}

//*****************************************************************

void Bird::moveDown()
{

    stoppingX();   

}

//*****************************************************************
/**
 *   Move the character by accelerating him
 */

void Bird::moveLeft()
{

    // Air movement Condition (check for ground state here, 
    //          in later versions)
    if(position.y != starting_y)
    {

        moveLeftRunning();        
        return;

    }

    if(velocity_vector.x > 0)
    {

        turning = 1;
        velocity_vector.x -= 2;

    }

    else if(velocity_vector.x > -10)
    {

        velocity_vector.x -= 2;

    }

    else 
    {

        velocity_vector.x = -10;

    }

    in_motion_right = 0;
    in_motion_left = 1;

}

//*****************************************************************
/**
 *   Move the character by accelerating him
 */

void Bird::moveRight()
{

    // Air movement Condition (check for ground state here, 
    //      in later versions)
    if(position.y != starting_y)
    {

        moveRightRunning();        
        return;

    }

    // If char was going left last frame
    if(velocity_vector.x < 0 )
    {

        turning = 1;
        velocity_vector.x += 2;

    }

    else if(velocity_vector.x < 10)
    {

        velocity_vector.x += 2;

    }

    else
    {

        velocity_vector.x = 10;

    }

    in_motion_right = 1;
    in_motion_left = 0;

}

//*****************************************************************
/**
 *   Move the character by accelerating him
 */

void Bird::moveLeftRunning()
{

    if(velocity_vector.x > 0)
    {

        turning = 1;
        velocity_vector.x -= 1;

    }

    else if(velocity_vector.x == 0)
    {

        velocity_vector.x = -3;

    }

    // Make sure character can only go so fast
    else if(vblank == 3 && 
            velocity_vector.x > -BIRD_MAX_X_VELOCITY)
    {

        velocity_vector.x -= 1;

    }

    in_motion_right = 0;
    in_motion_left = 1;

}

//*****************************************************************
/**
 *   Move the character by accelerating him
 */

void Bird::moveRightRunning()
{

    if(velocity_vector.x < 0)
    {

        turning = 1;
        velocity_vector.x += 1;

    }

    else if(velocity_vector.x == 0)
    {

        velocity_vector.x = +3;

    }

    else if(vblank == 3 && 
            velocity_vector.x < BIRD_MAX_X_VELOCITY)
    {

        velocity_vector.x += 1;

    }

    in_motion_right = 1;
    in_motion_left = 0;

}

//*****************************************************************

void Bird::stoppingX()
{

    // Do nothing if you are already stopped
    if(velocity_vector.x == 0)
    {

        return;

    }

    // If the character is not on the ground, 
    // dont stop/slowdown at all till you hit 
    //      the ground
    if(!(state & ON_GROUND))
    {

        return;

    }


    // If the dude was going left, and is stopping
    if(velocity_vector.x < 0)
    {

        // Apply friction force
        velocity_vector.x += 1;
        in_motion_right = 0;
        in_motion_left = 1;

    }

    // If the dude was going right, and is stopping
    else if(velocity_vector.x > 0)
    {

        // Apply friction force
        velocity_vector.x -= 1;
        in_motion_right = 1;
        in_motion_left = 0;

    }

}

//*****************************************************************

void Bird::updatePhysics()
{

    if(!in_motion_right && !in_motion_left && 
            position.y == starting_y)
    {

        //velocity_vector.x = 0;
        //applyFriction(&velocity_vector.x, 
        //      &velocity_vector.y, position_x, 
        //    position_y);

    }


    // Update the position (no shift operation to preserve sign)
    //      Optimize with shift?
    position += velocity_vector/4;   

    //applyGravity(&velocity_vector.x, &velocity_vector.y);    
    int temp = (velocity_vector.y<< 2) + 7;
    velocity_vector.y = temp >> 2;

    // Stop subtracting when it hits the bottom
    if(position.y >= starting_y )
    {

        // Make sure character does not fall through ground
        position.y = starting_y;

        state &= ~JUMPING; 
        state |= ON_GROUND;

        if(velocity_vector.y > 2)
        {

            // Sound for when we hit the ground 
            playImpactSound();

        }

        velocity_vector.y = 0;        

    }


}

//*****************************************************************
/**
 *   Animation for when bird jumps
 */

void Bird::updateGraphicJumping()
{

    if(frame_number < BIRD_JUMPING_FRAME_NUMBER ||
            frame_number > BIRD_JUMPING_FRAME2_NUMBER)
    {


        frame_number = BIRD_JUMPING_FRAME_NUMBER;

    }

    if(vblank == 3)
    {

        changeAnimationFrame(frame_number);
        frame_number++;
    }

    //-----------------------------------------
    //  Be sure to turn around while flying
    //     (no moonwalk flying)
    //-----------------------------------------
    if(velocity_vector.x > 0)
    {
        
        flipRight();

    }

    else
    {

        flipLeft();

    }


}

//*****************************************************************
/**
 *   Update the animation graphics and location
 *       So far there are MAX_ANIMATION_SPEEDS 
 *       levels of animation speed so account for these by
 *           BIRD_MAX_X_VELOCITY / MAX_ANIMATION_SPEEDS, 
 *           eventually?
 */

void Bird::updateGraphic(Vector2D orig_position)
{    

    //    Character::updateGraphic();
    //    static int frame_num = 0;
    //    
    //    Sprites::setTileGFX(
    //                (unsigned char*)bird_Tiles+BIRD_FRAME_SIZE*frame_num, 
    //                BIRD_FRAME_SIZE, gfx_memory_index);
    //    frame_num = (frame_num + 1)%10;
    //    return;

    //const int  = BIRD_MAX_X_VELOCITY / MAX_ANIMATION_SPEEDS;

    if(state & ON_GROUND)
    {

        updateGraphicOnGround();

    }

    else
    {

        // If char is jumping
        updateGraphicJumping();

    }

    if(vblank == 3)
    {

        vblank = 0;        

    }

    else
    {

        vblank++;

    }

    if(collision_flag < 1)
    {

        collision_flag++;

    }

    else
    {
        collision_flag = 0;
    }



    Character::updateGraphic();

}

//*****************************************************************
/**
 * 	 Updates the walking frame of Bird 
 * 	 (doesn't matter what direction facing)
 */

void Bird::updateWalkFrame()
{


    in_motion_right = 0;
    in_motion_left = 0;      

    frame_number++;

    if(frame_number < BIRD_WALK_RIGHT_FRAME_NUMBER
            || frame_number > BIRD_WALK_RIGHT_FRAME3_NUMBER)
    {

        frame_number = BIRD_WALK_RIGHT_FRAME_NUMBER;

    }

    changeAnimationFrame(frame_number);              

}

//*****************************************************************
/**
 *  Flip Sprite left
 */

void Bird::flipRight()
{

    // Make sure to flip vertical!
    if(!(state & FLIPPED))
    {

        Sprites::flipSpriteHorizontal(sprite_index);
        state |= FLIPPED;

    }


}


//*****************************************************************
/**
 *  Flip Sprite left
 */

void Bird::flipLeft()
{

    if(state & FLIPPED)
    {

        Sprites::flipSpriteHorizontal(sprite_index);
        state &= ~FLIPPED;

    }

}


//*****************************************************************
/**
 *    Update the walk right frames
 */

void Bird::updateWalkRightFrame()
{

    flipRight();

    updateWalkFrame();

}

//*****************************************************************
/**
 *  Update walk left frames
 */

void Bird::updateWalkLeftFrame()
{

    flipLeft();

    updateWalkFrame();

}

//*****************************************************************

void Bird::updateGraphicOnGround()
{

    if(in_motion_right && turning && 
            vblank <= BIRD_MAX_ANIMATION_SPEEDS)
    {

        changeAnimationFrame(BIRD_TURN_LEFT_FRAME_NUMBER);      
        if(state & FLIPPED)
        {
            Sprites::flipSpriteHorizontal(sprite_index);
            state &= !FLIPPED;
        }

        in_motion_right = 0;
        in_motion_left = 0; 
        turning = 0;

    }

    else if(in_motion_left && turning && 
            vblank <= BIRD_MAX_ANIMATION_SPEEDS)
    {

        changeAnimationFrame(BIRD_TURN_LEFT_FRAME_NUMBER);      

        if(!(state & FLIPPED))
        {

            Sprites::flipSpriteHorizontal(sprite_index);
            state |= FLIPPED;

        }

        in_motion_right = 0;
        in_motion_left = 0;                
        turning = 0;

    }

    // Update moving graphics every third vblank
    else if(in_motion_right && vblank == 3)
    {

        updateWalkRightFrame();

    }

    else if(in_motion_left && vblank == 3)
    {

        updateWalkLeftFrame();

    }

    // If Bird is standing still and not sliding
    else if(in_motion_left == 0 && 
            in_motion_right == 0)
    {

        if(~REG_KEYINPUT & KEY_DOWN)
        {

            
                changeAnimationFrame(BIRD_DUCKING_FRAME_NUMBER);   
            state |= DUCKING;


        }

        else
        {

            static int reached = 0;

            if(reached == 120 && reached>>4)
            {

                changeAnimationFrame(BIRD_BLINK_FRAME_NUMBER);
                reached = 0;

            }

            else if(reached >> 4)
            {

                changeAnimationFrame(BIRD_STAND_RIGHT_FRAME_NUMBER);     

            }
            state &= ~DUCKING;

            reached++;

        }

    }

}


//*****************************************************************

void Bird::changeAnimationFrame(int frame)
{

    frame_number = frame;
    if(separate_gfx)
    {

        Sprites::setTileGFX((unsigned char*)
                &bird_Tiles[64*32*frame], 
                BIRD_FRAME_SIZE, this->gfx_memory_index);

    }

    else
    {

        Sprites::setTileIndex(
                byteIndexToTileIndex(gfx_memory_index) +
                BIRD_TILES_PER_FRAME*frame, 
                sprite_index);

        /*
           Debug::printSetup();
           iprintf("\x1b[0;0H tile number: %03d",BIRD_TILES_PER_FRAME*frame);
           iprintf("\x1b[1;0H GFX[%04d]",32*32*frame);
           iprintf("\x1b[2;0H frame: %d",frame);
           iprintf("\x1b[3;0H char_index: %03d", 
           Sprites::getTileIndex(sprite_index));
         */

    }    

}

//********************************************************

void Bird::playJumpSound()
{

    // Jump sound effect
    kramPlayExt(samples[JUMP_SOUND_SAMPLE_NUMBER], 1, 0, 
            (int)(S3M_SAMPLE_FREQUENCY*3),80,64 ); 

}

//********************************************************

void Bird::playImpactSound()
{

    // Sound for when we hit the ground 
    //  (magic numbers are just to play with 
    //    effect frequency etc)
    //kramPlayExt(samples[14], 1, 0,
    //S3M_SAMPLE_FREQUENCY*2,32,0);

    playImpactSound(64);

}

//********************************************************
/**
 *   Play an impact sound with a given volume.
 *      USAGE: e.g. send the abs value of velocity 
 *      to this function.
 */

void Bird::playImpactSound(unsigned int volume)
{

    //    // Sound for when we hit the ground 
    //    //          (magic numbers are just to play with 
    //    //    effect frequency etc)
    //    kramPlayExt(samples[14], 1, 0,
    //            S3M_SAMPLE_FREQUENCY*2,32+3*volume/2,0);

}

