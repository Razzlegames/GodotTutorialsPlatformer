#include "world1_physics.h"

/**
*   Apply gravity to a current motion vector
*       @param vector_x velocity vectors
*       @param vector_y
*/

void applyGravity(int* velocity_vector_x, int* velocity_vector_y)
{
    if(*velocity_vector_y != 0 && *velocity_vector_y < TERMINAL_VELOCITY)
    {
        
        (*velocity_vector_y) = (*velocity_vector_y)+ GRAVITY_VECTOR;
    }
    else
    {
        *velocity_vector_y = TERMINAL_VELOCITY;
    }
}

/**
*   Apply friction if the character is touching anything
*       @param 
*/

void applyFriction(int* velocity_vector_x, int* velocity_vector_y, int position_x, int position_y)
{
    // Only apply x friction if character is touching floor
    if(position_y == FLOOR_POSITION && velocity_vector_x > 0)
    {
        *velocity_vector_x -= 1;
    }
    else if(position_y == FLOOR_POSITION && velocity_vector_x < 0)
    {
        *velocity_vector_x += 1;
    }
}
