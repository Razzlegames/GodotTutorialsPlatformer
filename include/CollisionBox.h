#ifndef COLLISIONBOX_H_
#define COLLISIONBOX_H_

#include "Vector2D.h"

/**
 *   Box to detect collisions, needs to be improved!
 */
class CollisionBox
{

  public:

      // Bottom Left Cordinate
      Vector2D bottom_left;
      Vector2D top_right;
      int width;
      int height;

      CollisionBox operator+(Vector2D p);
      CollisionBox operator-(Vector2D p);
      bool operator*(CollisionBox b);

      bool collisionCheck(int b1x, int  b1y, int t1x,
              int  t1y, int  b2x,int  b2y, int t2x, int t2y);
      bool verticiesMatch(CollisionBox c2);
      int above(CollisionBox b);
      int below(CollisionBox b);

};

//******************************************************************************
/**
 *  Check to see if a collision box is above you
 * 	(FYI: On GBA higher Y means below!!!, but coll box doesn't use)
 */
inline int CollisionBox::above(CollisionBox b)
{

    return (b.top_right.y >= top_right.y &&
            b.bottom_left.y >= bottom_left.y);	

}
//******************************************************************************
/**
 *  Check to see if a collision box is below you
 * 	(FYI: On GBA higher Y means below!!!, but coll box doesn't use)
 */
inline int CollisionBox::below(CollisionBox b)
{

    return !above(b);

}

#endif /*COLLISIONBOX_H_*/
