/* vim: set filetype=cpp.doxygen : */
#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H 

#include "Vector2D.h"
#include "Character.h"

class ICollide;
class IntersectionPairs;
class AABBEndPoint;

//*********************************************************************
/**
 *   AABB to use in Collision detection algorithm
 */
class AxisAlignedBoundingBox
{

  protected:

    Character* character;

    /// Position of box center (Object space)
    Vector2D center;

    /// min End point
    AABBEndPoint* min_point;

    /// max End point
    AABBEndPoint* max_point;

    /// If bounding box is Colliding with something during frame
    ///   (count of currently colliding boxes this has a relation with)
    int colliding;

    /// If Low level collision is happening
    int low_level_colliding;

  public:

    AxisAlignedBoundingBox():
        character(NULL),
        center(),
        min_point(NULL),
        max_point(NULL),
        colliding(0),
        low_level_colliding(0)
    {}

    virtual ~AxisAlignedBoundingBox()
    {}

    virtual void deleteCollision()
    {

        colliding--;
        if(colliding < 0) colliding = 0;
    }
    
    virtual void addCollision()
    {

        colliding++;
    }

    virtual void deleteLowLevelCollision()
    {

        low_level_colliding--;
        if(low_level_colliding < 0) low_level_colliding = 0;
        low_level_colliding = 0;
    }
    
    virtual void addLowLevelCollision()
    {

        low_level_colliding++;
    }


    Character* getCharacter()
    {

        return character;
    }

    virtual void create(Character* m) = 0;

    virtual int getMin(unsigned int cord) const = 0;
    virtual int getMax(unsigned int cord) const = 0;
    virtual AABBEndPoint* getMax() = 0;
    virtual AABBEndPoint* getMin() = 0;

    virtual void draw() = 0;
    inline virtual bool overlaps(AxisAlignedBoundingBox* e, 
            unsigned int cord);

    /// Get the position in World space
    virtual Vector2D* getPosition() = 0;

    //virtual std::ostream& print(std::ostream& o) = 0;

    friend class ICollide;
    //friend std::ostream& operator<< (std::ostream& o, 
    //const IntersectionPairs in);

};

//**********************************************************
/**
 *  Check to see if two bounding boxes overlap on a specific
 *    axis 
 *
 */

bool AxisAlignedBoundingBox::overlaps(AxisAlignedBoundingBox* b,
        unsigned int cord)
{

    //-------------------------------------------------------
    //  Checking the cord noted as X for being between 
    //     min and max end points
    //-------------------------------------------------------
    //
    //     B1               E1
    //     o----------------X
    //  B2                      E2
    //  o-----------------------o
    //
    if(b->getMax(cord) >= getMin(cord) &&
       b->getMax(cord) <= getMax(cord))
    {

        return true;
    }

    //-------------------------------------------------------
    //  Checking the cord noted as X for being between 
    //     min and max end points
    //-------------------------------------------------------
    //
    //     B2               E2
    //     o----------------o
    //  B1             E1
    //  o--------------X
    //
    if(getMax(cord) >= b->getMin(cord) &&
       getMax(cord) <= b->getMax(cord))
    {

        return true;
    }

    return false;

}


//*********************************************************************
/** 
 *   Help to keep track of AxisAlignedBoundingBox end points
 */

class AABBEndPoint
{

  public:

    static const enum {MIN_POINT, MAX_POINT} MinMax;

    /// Box this end point is refering to
    AxisAlignedBoundingBox* box;

    /// If the box represents the min or max cord of a bounding box
    int min_max;

    /// Value of the min or max value at any cord
    ///         (contains all two cords)
    Vector2D value;

    AABBEndPoint(AxisAlignedBoundingBox* b, int min_max):
        box(b),
        min_max(min_max)
    {

        assert(b != NULL);
    }

  private:
    AABBEndPoint(){}

  public:

    inline int getCord(unsigned int cord);

    inline int& operator [] (int index);
    //inline friend std::ostream& operator << 
    //(std::ostream& o, AABBEndPoint e);

};

//*********************************************************************
/**
 *   Compare End points to see if it is less than another
 */

int& AABBEndPoint::operator [] (int index)
{

    return value[index];

}

//*********************************************************************
/**
 *   Compare End points to see if it is less than another.
 *   
 *   @param cord cord cordinate value to extract, must be:
 *      #Vector2D::X_VALUE, #Vector2D::Y_VALUE 
 */

int AABBEndPoint::getCord(unsigned int cord)
{

    return value[cord] + (*(box->getPosition()))[cord];

}

////**********************************************************
///**
// *  Friend function for printing  to output streams
// */
//
//std::ostream& operator<< (std::ostream& o, AABBEndPoint e)
//{
//
//    return o << "min_max: " << e.min_max  << 
//        ", value: " << 
//        e.getCord(0) << 
//        e.getCord(1) << 
//        e.getCord(2);
//
//}



#endif /* AXISALIGNEDBOUNDINGBOX_H */
