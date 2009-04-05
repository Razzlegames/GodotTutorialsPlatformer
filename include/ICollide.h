/* vim: set filetype=cpp.doxygen : */
#ifndef ICOLLIDE_H
#define ICOLLIDE_H 

#include <list>
#include <vector>
#include <utility>
#include "Vector2D.h"
#include "AxisAlignedBoundingBox.h"
#include "FixedSizeBoundingBox.h"

//*********************************************************************
/**
 *   Keeps track of object intersections 
 */

class IntersectionPairs
{

  private:
    /// Flag that indicates if x axis overlaps in bounding box pair
    bool overlap_cord[2];

  public:

    /// Box that overlaps in at least 1 dimension
    AxisAlignedBoundingBox* b1;

    /// Box that overlaps in at least 1 dimension
    AxisAlignedBoundingBox* b2;

    /// If objects are colliding at a low level
    bool low_level_collision;

    IntersectionPairs():
        b1(NULL),
        b2(NULL),
        low_level_collision(false)
    {

        overlap_cord[0] = false;
        overlap_cord[1] = false;

    }

    IntersectionPairs(AxisAlignedBoundingBox* b1_p, 
            AxisAlignedBoundingBox* b2_p):
        b1(b1_p),
        b2(b2_p),
        low_level_collision(false)
    {

        // Arrange IDs in proper order (b1 <= b2)
        if(b1 > b2)
        {

            AxisAlignedBoundingBox* temp = b2;
            b2 = b1;
            b1 = temp;

        }


        overlap_cord[0] = false;
        overlap_cord[1] = false;

    }


    IntersectionPairs(AxisAlignedBoundingBox* b1_p, 
            AxisAlignedBoundingBox* b2_p, unsigned int cord):
        b1(b1_p),
        b2(b2_p)
    {

        // Arrange IDs in proper order (b1 <= b2)
        if(b1 > b2)
        {

            AxisAlignedBoundingBox* temp = b2;
            b2 = b1;
            b1 = temp;

        }

        overlap_cord[0] = false;
        overlap_cord[1] = false;

        overlap_cord[cord] = true;
    }

    bool operator ==(IntersectionPairs in)
    {

        if((b1 == in.b1 && b2 == in.b2) )
                // Not needed if b1 <= b2, always
                //|| (b1 == in.b2 && b2 == in.b1))
        {

            return true;
        }

        return false;
    }


    inline void addOverlap(unsigned int cord);
    inline void deleteOverlap(unsigned int cord);
    void indicateCollision();
    void indicateNoCollision();
    void checkLowLevelCollision();

    static void addPairToVector(std::vector<IntersectionPairs>& v,
            IntersectionPairs p);

    friend class ICollide;
    //friend std::ostream& operator<< (std::ostream& o, 
    //const IntersectionPairs in);

};


//*********************************************************************

class ICollide
{

  public:

      //    /// The current model to world transform done by the engine
      //    ///    (needed only to transform faces underneath the bounding boxes
      //    ///    as to test Exact collision with these faces).
      //    Matrix<float>* model_to_world_matrix;

  private:
      /// Axis aligned boxes that this System will use
      std::vector<AxisAlignedBoundingBox*> m_boxes;

      /// List with each bounding box sorted based on minx value
      std::vector<AABBEndPoint*> x_list;

      /// List with each bounding box sorted based on miny value
      std::vector<AABBEndPoint*> y_list;

    /// List of pairs of Bounding boxes with at least one intersection
    ///   (on one axis)
      std::vector<IntersectionPairs> active_pairs;

  public:
    ICollide();
    void updateLists();

    void create(std::vector<AxisAlignedBoundingBox*> boxes);

    //void createFixedCubes(std::vector<Mesh*> meshes);
    void createFixed2DBoxes(std::vector<Character*> characters);
    void addFixedBoxes(std::vector<Character*> characters);

    void addBoxes(std::vector<AxisAlignedBoundingBox*> boxes);
    void addBoxesEndPoints(std::vector<AxisAlignedBoundingBox*> boxes);
    
    void insertion_sort(std::vector<AABBEndPoint*> l, 
        unsigned int cord);

    void bubble_sort(std::vector<AABBEndPoint*>& l, 
            unsigned int cord);

    void drawBoundingBoxes();
    void drawBoundingBoxesAndMeshes(bool boxes);

    void addActivePair(AxisAlignedBoundingBox* b1, 
            AxisAlignedBoundingBox* b2, unsigned int cord);
    void deleteActivePair(AxisAlignedBoundingBox* b1, 
            AxisAlignedBoundingBox* b2, unsigned int cord);

    void checkPossibleOverlaps(std::vector<IntersectionPairs> possible,
            unsigned int cord);

    void checkOverlapOnSwap(AABBEndPoint* greater, 
            AABBEndPoint* less, unsigned int cord);

    void initActivePairs();

    void printActivePairs();
    void printBoundingBoxes();

};


#endif /* ICOLLIDE_H */

