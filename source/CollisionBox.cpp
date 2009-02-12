#include "CollisionBox.h"



//******************************************************************************
/**
 *    Check two collision boxes for intersection
 * 	    It would be a good idea to check for both cases of intersection
 */
bool CollisionBox::operator*(CollisionBox b)
{

    return collisionCheck(bottom_left.x, bottom_left.y,
            top_right.x, top_right.y, 
            b.bottom_left.x, b.bottom_left.y,
            b.top_right.x, b.top_right.y) ||
        collisionCheck(b.bottom_left.x, b.bottom_left.y,
                b.top_right.x, b.top_right.y,
                bottom_left.x, bottom_left.y,
                top_right.x, top_right.y) ||
        // Check if any verticies match
        collisionCheck(b);

}

//******************************************************************************
/**
 * 		Add a position to the CollisionBox Cords
 */
CollisionBox CollisionBox::operator+(Vector2D p)
{
    CollisionBox c = *this;
    c.bottom_left += p;
    c.top_right += p;
    return c;
}

//******************************************************************************
/**
 * 		Subtract a position to the CollisionBox Cords
 */
CollisionBox CollisionBox::operator-(Vector2D p)
{
    CollisionBox c = *this;
    c.bottom_left -= p;
    c.top_right -= p;
    return c;
}

//******************************************************************************
bool CollisionBox::collisionCheck(CollisionBox c2)
{ 

    if(c2.bottom_left == bottom_left || 
            (c2.bottom_left == Vector2D(bottom_left.x,top_right.y)) ||
            c2.bottom_left == top_right || 
            c2.bottom_left == Vector2D(top_right.x,bottom_left.y))
    {
        return true;
    }
    else if(c2.top_right == bottom_left || 
            (c2.top_right == Vector2D(bottom_left.x,top_right.y)) ||
            c2.top_right == top_right || 
            c2.top_right == Vector2D(top_right.x,bottom_left.y))
    {
        return true;
    }
    else if(Vector2D(c2.bottom_left.x,c2.top_right.y) == bottom_left || 
            (Vector2D(c2.bottom_left.x,c2.top_right.y)== 
             Vector2D(bottom_left.x,top_right.y)) ||
            Vector2D(c2.bottom_left.x,c2.top_right.y) == top_right || 
            Vector2D(c2.bottom_left.x,c2.top_right.y) == 
            Vector2D(top_right.x,bottom_left.y))
    {
        return true;
    }
    else if(Vector2D(c2.top_right.x,c2.bottom_left.y) == bottom_left || 
            (Vector2D(c2.top_right.x,c2.bottom_left.y)  == 
             Vector2D(bottom_left.x,top_right.y)) ||
            Vector2D(c2.top_right.x,c2.bottom_left.y)  == top_right || 
            Vector2D(c2.top_right.x,c2.bottom_left.y)  == 
            Vector2D(top_right.x,bottom_left.y))
    {
        return true;
    }
    return false;

}
//******************************************************************************
/**
 *    Check two collision boxes for intersection
 * 	    It would be a good idea to check for both cases of intersection
 * 
 * 	\param b1x bottom x cord of 1 box
 * 	\param b1y bottom y cord of 1 box
 * 	\param t1x top x cord of 1 box
 *  \param t1y top y cord of 1 box
 * 	\param b2x bottom x cord of 2 box
 * 	\param b2y bottom y cord of 2 box
 * 	\param t2x top x cord of 2 box
 * 	\param t2y top y cord of 2 box
 * 
 */
bool CollisionBox::collisionCheck(float b1x, float  b1y, float t1x,
        float  t1y, float  b2x,float  b2y, float t2x, float t2y)
{
    static int collision_count = 0;
    // Check if any point is within x cord, and within either box
    /* -------      
     * | |---|---|
     * |_|___|   |
     *   |_______|
     */
    if((t1x >= b2x && t2x >= t1x) && (b1y <= t2y && t1y >= t2y) ||
            ((t1x >= b2x && b2x >= b1x) && (b2y >= b1y && b2y <= t1y)) ||
            ((t1x >= b2x && t1x <= t2x) && (t1y >= b2y && t2y >= t1y))||
            ((t1x >= b2x && t1x <= t2x) && (b1y >= b2y && b1y <= t2y)))
    {	
        /*		 
        // Collision debug data printing
        printf("collision_count: %d\n",collision_count++);
        printf("(b1x,b1y):(t1x,t1y): (%f,%f):(%f,%f)\n",b1x,b1y,
        t1x,t1y);
        printf("(b2x,b2y):(t2x,t2y): (%f,%f):(%f,%f)\n",b2x,b2y,
        t2x,t2y);
         */
        return true;

    }
    return false;
}

