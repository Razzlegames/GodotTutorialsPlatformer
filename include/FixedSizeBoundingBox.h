/* vim: set filetype=cpp.doxygen : */
#ifndef FIXEDSIZEBOUNDINGBOX_H
#define FIXEDSIZEBOUNDINGBOX_H 

#include "Vector2D.h"
#include "AxisAlignedBoundingBox.h"
#include "Character.h"


class FixedSizeBoundingBox: public AxisAlignedBoundingBox
{

  protected:
    using AxisAlignedBoundingBox::character;

    /// Width of box (from box left to right)
    int width;

    /// Height of box (from top to bottom)
    int height;

    //using AxisAlignedBoundingBox::center;

    // AABBEndPoint 
    using AxisAlignedBoundingBox::min_point;
    // AABBEndPoint 
    using AxisAlignedBoundingBox::max_point;
    // bool
    using AxisAlignedBoundingBox::colliding;

    /// Position of box center (World Space)
    Vector2D* position;

  public:
    FixedSizeBoundingBox(Character* m);

    virtual ~FixedSizeBoundingBox()
    {

    }

    virtual void create(Character* m);

    virtual int getMin(unsigned int cord) const;
    virtual int getMax(unsigned int cord) const ;
    virtual AABBEndPoint* getMax() ;
    virtual AABBEndPoint* getMin() ;

    void draw() ;
    //    inline virtual bool overlaps(AxisAlignedBoundingBox* e, 
    //            unsigned int cord);

    //void computeCenter(Character* character);
    //void computeRadius(Character* character);

    void computeEndPoints();

    /// Get the position in World space
    virtual Vector2D* getPosition() ;


    //    std::ostream& print(std::ostream& o);
    //
    //    friend std::ostream& operator<< (std::ostream& o, 
    //            FixedSizeBoundingCube b);

    friend class ICollide;

};

#endif /* FIXEDSIZEBOUNDINGBOX_H */
