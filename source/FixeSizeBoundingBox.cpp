/* vim: set filetype=cpp.doxygen : */

#include "FixedSizeBoundingBox.h"

using namespace std;


//*********************************************************************
/**
 */

FixedSizeBoundingBox::FixedSizeBoundingBox(Character* m):
    AxisAlignedBoundingBox()
{

    character = m;
    create(m);
}

//*********************************************************************
/**
 *   Get the min cord value (In World Space!)
 *   @param cord cordinate value to extract, must be:
 *      #Vector3D::X_VALUE, #Vector3D::Y_VALUE, #Vector3D::Z_VALUE
 */

int FixedSizeBoundingBox::getMin(unsigned int cord) const
{

    // World space transform handled by AABBEndPoint::getCord(cord)
    return min_point->getCord(cord);
}


//*********************************************************************
/**
 *   Get the min cord value (In Object Space!)
 *   @param cord cordinate value to extract, must be:
 *      #Vector3D::X_VALUE, #Vector3D::Y_VALUE, #Vector3D::Z_VALUE
 */

AABBEndPoint* FixedSizeBoundingBox::getMax()
{

    return max_point;
}


//*********************************************************************
/**
 *   Get the min cord value (In Object Space!)
 *   @param cord cordinate value to extract, must be:
 *      #Vector3D::X_VALUE, #Vector3D::Y_VALUE, #Vector3D::Z_VALUE
 */

AABBEndPoint* FixedSizeBoundingBox::getMin()
{

    return min_point;
}


//*********************************************************************
/**
 *   Get the min cord value (In World Space!)
 *   @param cord cordinate value to extract, must be:
 *      #Vector3D::X_VALUE, #Vector3D::Y_VALUE, #Vector3D::Z_VALUE
 */

int FixedSizeBoundingBox::getMax(unsigned int cord) const
{

    // World space transform handled by AABBEndPoint::getCord(cord)
    return max_point->getCord(cord);
}



//*********************************************************************
/**
 *   Build a fixed cube based on a triangle character
 */

void FixedSizeBoundingBox::create(Character* character)
{

    assert(character!= NULL);

    position = &(character->position);
    //computeCenter(character);
    //computeRadius(character);
    this->character = character;
    computeEndPoints();

}

//**********************************************************
/**
 *   Compute end points for the Fixed AABB
 *     (assumes #radius and #center  have already been 
 *     computed!)
 */

void FixedSizeBoundingBox::computeEndPoints()
{

    min_point = new AABBEndPoint(this, AABBEndPoint::MIN_POINT);
    max_point = new AABBEndPoint(this, AABBEndPoint::MAX_POINT);

    // Compute min point
    min_point->value = Vector2D(0,0);

    // Compute max point
    max_point->value = Vector2D(width, height);

}

////**********************************************************
///**
// *  Compute object space center of a Character
// */
//
//void FixedSizeBoundingBox::computeCenter(Character* character)
//{
//
//    assert(character != NULL);
//    center = character->computeCenter();
//
//}

////**********************************************************
///**
// *  Compute radius of bounding box, assume center was already 
// *   computed, Max distance for the BB center to any vertex
// *   of the character.
// *
// *
// *  @param character character to compute radius from
// */ 
//
//void FixedSizeBoundingBox::computeRadius(Character* character)
//{
//
//}

//**********************************************************
/**
 *   @return Get the reference position for this bounding box
 */
Vector2D* FixedSizeBoundingBox::getPosition()
{

    return position;
}

//**********************************************************
/**
 *   Draw the bounding box
 */

void FixedSizeBoundingBox::draw()
{
}

////**********************************************************
///**
// *  Friend function for printing  to output streams
// */
//
//std::ostream& FixedSizeBoundingBox::print (std::ostream& o)
//{
//
//    return o 
//        << "colliding: " << colliding << "\n" 
//        << "center: " << center << "\n" 
//        << "min_point: " << min_point->value << "\n"
//        << "max_point: " << max_point->value << "\n"
//        << "position: " << *(getPosition()) << "\n" 
//
//        << "world min (" << getMin(0) << "," << getMin(1) << "," 
//        << getMin(2) << ")\n"
//
//        << "world max (" << getMax(0) << "," << getMax(1) << "," 
//        << getMax(2) << ")";
//
//}
//
////**********************************************************
///**
// *  Friend function for printing  to output streams
// */
//
//std::ostream& operator<< (std::ostream& o, 
//        FixedSizeBoundingBox box)
//{
//
//    return o << "center: " << box.center 
//        << "box.min_point: " << box.min_point->value << 
//        "box.max_point: " << box.max_point->value
//        << "position: " << box.getPosition() << "\n" 
//        << "world min (" << box.getMin(0) << "," << box.getMin(1) << "," 
//        << box.getMin(2) << ")\n"
//        << "world max (" << box.getMax(0) << "," << box.getMax(1) << "," 
//        << box.getMax(2) << ")";
//
//
//}



