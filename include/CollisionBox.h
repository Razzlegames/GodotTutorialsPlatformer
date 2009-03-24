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
      float width;
      float height;

      CollisionBox operator+(Vector2D p);
      CollisionBox operator-(Vector2D p);
      bool operator*(CollisionBox b);

      bool collisionCheck(float b1x, float  b1y, float t1x,
              float  t1y, float  b2x,float  b2y, float t2x, float t2y);
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
