#include "CollisionBox.h"



//***********************************************************************
/**
 *    Check two collision boxes for intersection
 * 	    It would be a good idea to check for both cases of intersection
 */

bool CollisionBox::operator*(CollisionBox b)
{

    // Takes care of calling both cases b-collides(c) c-collides(b)
    return collisionCheck(b) ||
        b.collisionCheck(*this);

}

//***********************************************************************
/**
 * 	Add a position to the CollisionBox Cords
 */

CollisionBox CollisionBox::operator+(Vector2D p)
{

    CollisionBox c = *this;
    c.bottom_left += p;
    c.top_right += p;

    return c;

}

//**********************************************************************
/**
 * 	Subtract a position to the CollisionBox Cords
 */

CollisionBox CollisionBox::operator-(Vector2D p)
{

    CollisionBox c = *this;
    c.bottom_left -= p;
    c.top_right -= p;

    return c;

}

//***********************************************************************
/**
 *   Check for a collision with box @p c (needs to be called in 
 *      reverse also to be complete c.collisionCheck(b) ||
 *      b.collisionCheck(c), etc
 *
 *   @param c box to check for collisions with
 *
 */

bool CollisionBox::collisionCheck(CollisionBox c)
{

    //----------------------------------
    // Check x cord for overlap
    //----------------------------------
    //
    //    |_______________|
    //    bl.x            tr.x
    // |____________|   
    // c.b1.x       c.tr.x
    //
    // Check that c.tr.x is within b1.x & tr.x
    // 

    if((top_right.x >= c.top_right.x &&
            bottom_left.x <= c.top_right.x) ||

    // |_______________|
    // bl.x            tr.x
    //      |____________|   
    //      c.b1.x       c.tr.x
    // 
    // Check that c.b1.x is within b1.x & tr.x
    //

     (top_right.x >= c.bottom_left.x &&
            bottom_left.x <= c.bottom_left.x))
    {


    }
    else 
    {

        return false;

    }
            
    //----------------------------------
    // Check y cord for overlap
    //----------------------------------
    //
    //    |_______________|
    //    bl.y            tr.y
    // |____________|   
    // c.b1.y       c.tr.y
    //
    // Check that c.tr.y is within b1.y & tr.y
    // 

    if((top_right.y >= c.top_right.y &&
            bottom_left.y <= c.top_right.y) ||

    // |_______________|
    // bl.y            tr.y
    //      |____________|   
    //      c.b1.y       c.tr.y
    // 
    // Check that c.b1.y is within b1.y & tr.y
            
     (top_right.y >= c.bottom_left.y &&
            bottom_left.y <= c.bottom_left.y))
    {


    }
    else 
    {

        return false;

    }

    return true;

}

