#include "CollisionBox.h"



//***********************************************************************
/**
 *    Check two collision boxes for intersection
 * 	    It would be a good idea to check for both cases of intersection
 */

bool CollisionBox::operator*(CollisionBox b)
{

    //    return collisionCheck(bottom_left.x, bottom_left.y,
    //            top_right.x, top_right.y, 
    //            b.bottom_left.x, b.bottom_left.y,
    //            b.top_right.x, b.top_right.y) ||
    //        collisionCheck(b.bottom_left.x, b.bottom_left.y,
    //                b.top_right.x, b.top_right.y,
    //                bottom_left.x, bottom_left.y,
    //                top_right.x, top_right.y) ||
    //        // Check if any verticies match
    //        verticiesMatch(b);

    // Takes care of calling both cases b-collides(c) c-collides(b)
    return collisionCheck(b) ||
        b.collisionCheck(*this);

}

//***********************************************************************
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

//**********************************************************************
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

//**********************************************************************

//bool CollisionBox::verticiesMatch(CollisionBox c2)
//{ 
//
//    if(c2.bottom_left == bottom_left || 
//            (c2.bottom_left == Vector2D(bottom_left.x,top_right.y)) ||
//            c2.bottom_left == top_right || 
//            c2.bottom_left == Vector2D(top_right.x,bottom_left.y))
//    {
//
//        return true;
//    }
//
//    else if(c2.top_right == bottom_left || 
//            (c2.top_right == Vector2D(bottom_left.x,top_right.y)) ||
//            c2.top_right == top_right || 
//            c2.top_right == Vector2D(top_right.x,bottom_left.y))
//    {
//
//        return true;
//    }
//
//    else if(Vector2D(c2.bottom_left.x,c2.top_right.y) == bottom_left || 
//            (Vector2D(c2.bottom_left.x,c2.top_right.y)== 
//             Vector2D(bottom_left.x,top_right.y)) ||
//            Vector2D(c2.bottom_left.x,c2.top_right.y) == top_right || 
//            Vector2D(c2.bottom_left.x,c2.top_right.y) == 
//            Vector2D(top_right.x,bottom_left.y))
//    {
//
//        return true;
//    }
//
//    else if(Vector2D(c2.top_right.x,c2.bottom_left.y) == bottom_left || 
//            (Vector2D(c2.top_right.x,c2.bottom_left.y)  == 
//             Vector2D(bottom_left.x,top_right.y)) ||
//            Vector2D(c2.top_right.x,c2.bottom_left.y)  == top_right || 
//            Vector2D(c2.top_right.x,c2.bottom_left.y)  == 
//            Vector2D(top_right.x,bottom_left.y))
//    {
//
//        return true;
//    }
//
//    return false;
//
//}

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

//***********************************************************************
/**
 *    Check two collision boxes for intersection
 * 	    It would be a good idea to check for both cases of intersection
 * 
 * 	@param b1x bottom x cord of 1 box
 * 	@param b1y bottom y cord of 1 box
 * 	@param t1x top x cord of 1 box
 *  @param t1y top y cord of 1 box
 * 	@param b2x bottom x cord of 2 box
 * 	@param b2y bottom y cord of 2 box
 * 	@param t2x top x cord of 2 box
 * 	@param t2y top y cord of 2 box
 * 
 */

bool CollisionBox::collisionCheck(int b1x, int  b1y, int t1x,
        int  t1y, int  b2x,int  b2y, int t2x, int t2y)
{

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

        //        // Collision debug data printing
        //        printf("collision_count: %d\n",collision_count++);
        //        printf("(b1x,b1y):(t1x,t1y): (%f,%f):"
        //        "(%f,%f)\n",b1x,b1y,
        //        t1x,t1y);
        //        printf("(b2x,b2y):(t2x,t2y): (%f,%f):(%f,%f)\n",
        //        b2x,b2y,t2x,t2y);

        return true;

    }

    return false;
}

