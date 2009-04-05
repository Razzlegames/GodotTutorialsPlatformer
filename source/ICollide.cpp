/* vim: set filetype=cpp.doxygen : */

#include "ICollide.h"
#include <algorithm>

using namespace std;

//*********************************************************************
/** 
 *   Add a Intersection pair to a vector (acting as a set)
 */

void IntersectionPairs::addPairToVector(
        std::vector<IntersectionPairs>& v,
        IntersectionPairs p)
{

    // If there's a duplicate entry, just ignore this insert
    for(unsigned int i = 0; i < v.size(); i++)
    {

        if(v[i] == p)
        {

            return;
        }

    }

    v.push_back(p);

}

//*********************************************************************
/**
 *   Add an overlap condition to a cord in Intersection pair
 */

void IntersectionPairs::addOverlap(unsigned int cord)
{

    assert(cord < 2);

    bool previous_f = false;

    if(!overlap_cord[cord]) previous_f = true;

    overlap_cord[cord] = true;

    // Keep track of colliding boxes
    //   (If previously false, and all cords are now true, increment 
    //    collision count)
    if(previous_f && overlap_cord[0] && overlap_cord[1] )
    {

        indicateCollision();

    }

}

//*********************************************************************
/**
 *  Add a collision to the pair's bounding boxes and check
 *    Low level details to see if collision is actually occuring 
 *    on primitives
 */

void IntersectionPairs::indicateCollision()
{

        b1->addCollision();
        b2->addCollision();

}

//*********************************************************************
/**
 *  Check for low level collisions
 *
 */

void IntersectionPairs::checkLowLevelCollision()
{

    // If the boxes are overlaping in all cords, check the low
    //   level collision using baraffs.
    if(overlap_cord[0] && overlap_cord[1] )
    {

        low_level_collision = true;

        b1->addLowLevelCollision();
        b2->addLowLevelCollision();

    }
    else
    {

        low_level_collision = false;
    }

}

//*********************************************************************
/**
 *
 *   Indicate that no collision is occuring on this Interection pair
 */

void IntersectionPairs::indicateNoCollision()
{

        b1->deleteCollision();
        b2->deleteCollision();

        // if bounding boxes aren't colliding, there's no way
        //   low level primitives are
        low_level_collision = false;

}

//*********************************************************************
/**
 *   Delete an overlap condition to a cord in Intersection pair
 */

void IntersectionPairs::deleteOverlap(unsigned int cord)
{

    assert(cord < 3);

    // Keep track of colliding boxes
    //   (If all cords were previously true, and now one will be 
    //   marked false, decrement collision count)
    if(overlap_cord[0] && overlap_cord[1] )
    {

        indicateNoCollision();
        b1->deleteLowLevelCollision();
        b2->deleteLowLevelCollision();
    }

    overlap_cord[cord] = false;
    low_level_collision = false;

}

//*********************************************************************

ICollide::ICollide():
    //model_to_world_matrix(NULL),
    m_boxes(),
    x_list(),
    y_list(),
    active_pairs()
{

}

//*********************************************************************
/**
 *   Update the lists of bounding boxes, appropriate to call each
 *   frame if any object moves.
 *
 */

void ICollide::updateLists()
{

    bubble_sort(x_list, Vector2D::X_CORD);
    bubble_sort(y_list, Vector2D::Y_CORD);

    //--------------------------------------------------------
    //  Check for collisions for each pair at the low level
    //    (only if entire bounding box overlaps)
    //--------------------------------------------------------
    vector<IntersectionPairs>::iterator itr;
    itr = active_pairs.begin();
    while(itr != active_pairs.end())
    {

        itr->checkLowLevelCollision();
        ++itr;
    }

}

//*********************************************************************
/**
 *    A bubble sort of all end points in a given @p cord axis.
 *
 *    @param l list to sort
 *    @param cord cord axis to sort on
 *
 */

void ICollide::bubble_sort(vector<AABBEndPoint*>& l, 
        unsigned int cord)
{

    // Keep track of possible intersections to check
    vector<IntersectionPairs> possible;

    bool any_swapped = false;
    bool swapped = false;

    do
    {

        swapped = false;

        for(unsigned int i = 0; i < l.size()-1; i++)
        {

            if( l[i]->getCord(cord) > l[i+1]->getCord(cord) )
            {

                checkOverlapOnSwap(l[i], l[i+1], cord);

                // Swap em
                //swap(l[i], l[i+1]);
                AABBEndPoint* temp = l[i];
                l[i] = l[i+1];
                l[i+1] = temp;

                swapped = true;
                any_swapped = true;

            }

        }

    }while(swapped);

}

//*********************************************************************
/**
 *   Utility for sorting Boundingboxes beginning/end points 
 *   from min to max.
 *
 *   @param l end points of boxes to sort from min to max
 *   @param cord cord axis to sort on
 *
 */

void ICollide::insertion_sort(vector<AABBEndPoint*> l, 
        unsigned int cord)
{

    // Keep track of possible intersections to check
    vector<IntersectionPairs> possible;

    bool swapped = false;
    AABBEndPoint* key;
    int i;
    for(unsigned int j = 1; j < l.size(); j++)
    {

        key = l[j];
        i=j-1;

        while( i >= 0 && l[i]->getCord(cord) > key->getCord(cord) )
        {

            checkOverlapOnSwap(l[i], key, cord);

            // Push all greater elements ahead in the list 
            //   to insert the key before them
            //   (any "pushed ahead" elements could be potential overlaps)
            l[i+1]=l[i];
            i--;

            swapped = true;

        }

        l[i+1]=key;

    }

    //    if(swapped)
    //    {
    //
    //        printActivePairs();
    //    }

}

//*********************************************************************
/**
 *  Create the initial overlap list
 */

void ICollide::initActivePairs()
{

    for(unsigned int i = 0; i < m_boxes.size(); i++)
    {

        for(unsigned int a = 0; a < m_boxes.size(); a++)
        {

            for(int cord = 0; cord < 3; cord++)
            {

                if(m_boxes[a]->overlaps( m_boxes[i], cord))
                {

                    addActivePair(m_boxes[a], m_boxes[i],
                            cord);

                }

            }

        }

    }

}

//*********************************************************************
/**
 *   Print out active pairs list, for debug
 */

void ICollide::printActivePairs()
{

    //    cout << "Active Pairs: ";
    //    for(unsigned int i = 0; i < active_pairs.size(); i++)
    //    {
    //
    //        cout << active_pairs[i];
    //    }
    //    cout << endl;

}

//*********************************************************************
/**
 *   Print out active pairs list, for debug
 */

void ICollide::printBoundingBoxes()
{

    //    cout << "Bounding Boxes: \n";
    //    for(unsigned int i = 0; i < m_boxes.size(); i++)
    //    {
    //
    //        cout << 
    //            "-----------------------------------------\n" <<
    //            "    Box: " << i << "\n" <<
    //            "-----------------------------------------\n";
    //         m_boxes[i]->print(cout) << "\n";
    //
    //    }
    //    cout << endl;

}


//*********************************************************************
/**
 *   When swapping check the End points to see if an overlap now
 *     occurs, if it does it adds to an #active_pairs list
 *     of overlaping boxes, it it is found to not overlap,
 *     it is deleted from a list of #active_pairs
 *
 *   @param greater the end point with the now greater value
 *   @param less the end point with the now lesser value
 *   @param cord cord axis to check overlap on
 *
 */

void ICollide::checkOverlapOnSwap(AABBEndPoint* greater, 
        AABBEndPoint* less, unsigned int cord)
{

    //    cout << "checkOverlapOnSwap: ";
    //    cout << "greater: " <<  *greater << "\n"
    //        << "less: " << *less << endl;
    // If A > B and A.MAX_POINT and B.MIN_POINT
    //   These boxes overlap!
    if(greater->min_max == AABBEndPoint::MAX_POINT &&
            less->min_max == AABBEndPoint::MIN_POINT)
    {

        //cout << "ADDED: active pair " << endl;
        addActivePair(greater->box, less->box, cord);

    }

    // If A > B and A.MIN_POINT and B.MAX_POINT
    //   These boxes DO NOT overlap!
    else if(greater->min_max == AABBEndPoint::MIN_POINT &&
            less->min_max == AABBEndPoint::MAX_POINT)
    {

        //cout << "DELETED: active pair " << endl;
        deleteActivePair(greater->box, less->box, cord);

    }

}


//*********************************************************************
/**
 *   See if any possible intersection pairs overlap, if they 
 *   do add them to the active pairs list.
 *
 *   @param possible possible intersections taken from the 
 *      sorting algorithim
 *   @param cord the axis these possible intersections were on
 */

void ICollide::checkPossibleOverlaps(vector<IntersectionPairs> possible,
        unsigned int cord)
{

    for(unsigned int i = 0; i < possible.size(); i++)
    {

        if(possible[i].b1->overlaps( possible[i].b2, cord))
        {

            addActivePair(possible[i].b1, possible[i].b2,
                    cord);
        }

    }

}

//*********************************************************************
/**
 *  Add a pair to the active pairs of collision boxes
 */

void ICollide::addActivePair(AxisAlignedBoundingBox* b1, 
        AxisAlignedBoundingBox* b2, unsigned int cord)
{

    //cout << "addActivePair" << endl;
    // Don't add the pair if it is a pair with itself
    if(b1 == b2 )
    {

        return;
    }

    IntersectionPairs temp(b1,b2,cord);

    // look for repeat of this pair that already exists
    for(unsigned int i = 0; i < active_pairs.size(); i++)
    {

        // If the Pair already exists just update the flag and 
        //   return
        if((active_pairs[i]) == temp)
        {

            active_pairs[i].addOverlap(cord);
            return;

        }

    }

    // If the pair was not found, create it, and 
    //    add it to the list of active pairs
    //IntersectionPairs* in = new IntersectionPairs(b1,b2,cord);
    IntersectionPairs::addPairToVector(active_pairs, temp);

}

//*********************************************************************
/**
 *   Remove an active pair of collisions from the list
 */

void ICollide::deleteActivePair(AxisAlignedBoundingBox* b1, 
        AxisAlignedBoundingBox* b2, unsigned int cord)
{

    // Don't add the pair if it is a pair with itself
    if(b1 == b2)
    {

        return;
    }

    IntersectionPairs temp(b1,b2,cord);

    //----------------------------------------------------------
    // look for repeat of this pair that already exists
    //----------------------------------------------------------
    vector<IntersectionPairs>::iterator itr = active_pairs.begin();

    // If the element has been removed from the list
    bool removed = false;

    while(itr != active_pairs.end() && !removed)
    {

        // If the Pair already exists just update the flag and 
        //   return
        if(*itr == temp)
        {

            // Set the overlap status on this active pairs cord to false
            itr->deleteOverlap(cord);

            // If all the cords no longer overlap, kick it out of the 
            //   active pairs list
            if(itr->overlap_cord[0] == false && 
                    itr->overlap_cord[1] == false && 
                    itr->overlap_cord[2] == false)
            {

                active_pairs.erase(itr);

            }

            removed = true;
        }

        ++itr;
    }

}

//*********************************************************************
/**
 *   Add boxes to the already existing lists.
 *
 * @param boxes boxes to add to the collision system
 *
 */

void ICollide::addBoxesEndPoints(vector<AxisAlignedBoundingBox*> boxes)
{

    for(unsigned int i = 0; i < boxes.size(); i++)
    {

        // New points as they are being created
        AABBEndPoint* min_point;
        AABBEndPoint* max_point;

        // iterator used for new point placement
        vector<AABBEndPoint* >::iterator itr;

        //-----------------------------------------------
        // Set up End points
        //-----------------------------------------------
        min_point = boxes[i]->getMin();
        max_point = boxes[i]->getMax();

        //-----------------------------------------------
        // Set up Xcord
        //-----------------------------------------------

        // Place new min point in list
        itr = x_list.begin();
        while(itr != x_list.end() && 
                (*itr)->getCord(0) < min_point->getCord(0))
        {

            ++itr;
        }
        x_list.insert(itr, min_point);

        // Place new max point in list
        itr = x_list.begin();
        while(itr != x_list.end() && 
                (*itr)->getCord(0) < max_point->getCord(0))
        {

            ++itr;
        }
        x_list.insert(itr, max_point);

        //-----------------------------------------------
        // Set up Y_CORD
        //-----------------------------------------------

        // Place new min point in list
        itr = y_list.begin();
        while(itr != y_list.end() && 
                (*itr)->getCord(1) < min_point->getCord(1))
        {

            ++itr;
        }
        y_list.insert(itr, min_point);


        // Place new max point in list
        itr = y_list.begin();
        while(itr != y_list.end() && 
                (*itr)->getCord(1) < max_point->getCord(1))
        {

            ++itr;
        }
        y_list.insert(itr, max_point);


    }

}

//*********************************************************************
/**
 *   Append @p boxes to the current vector of active collision boxes
 *     and create all end points to be organized in X,Y,Z lists.
 *
 *     @param boxes AA Bounding boxes to add
 */

void ICollide::addBoxes(vector<AxisAlignedBoundingBox*> boxes)
{

    // Append the boxes
    m_boxes.insert(m_boxes.end(), boxes.begin(), boxes.end());
    addBoxesEndPoints(boxes);

}

//*********************************************************************
/**
 *   Initial creation of ICollide system using a set of Axis aligned 
 *   Bounding boxes.
 *
 *   @param boxes the AABB to create the ICollide system from
 */

void ICollide::create(vector<AxisAlignedBoundingBox*> boxes)
{

    m_boxes.clear();
    x_list.clear();
    y_list.clear();

    addBoxes(boxes);

}

////*********************************************************************
///**
// *   Create ICollide system with all FixedSizeBoundingCube s.
// *
// *   @param meshes meshes to create a Collision detection 
// *      system from
// *
// */
//
//void ICollide::createFixedCubes(vector<Mesh*> meshes)
//{
//
//    m_boxes.clear();
//    x_list.clear();
//    y_list.clear();
//
//    addFixedCubes(meshes);
//    initActivePairs();
//
//}


//*********************************************************************
/**
 *   Create ICollide system with all FixedSizeBoundingBoxes.
 *
 *   @param characters characters to create a Collision detection 
 *      system from
 *
 */

void ICollide::createFixed2DBoxes(std::vector<Character*> characters)
{

    m_boxes.clear();
    x_list.clear();
    y_list.clear();

    //addFixedCubes(characters);
    initActivePairs();


}

//*********************************************************************
/**
 *   Add to ICollide system with all FixedSizeBoundingBox s.
 *
 *   @param characters characters to create a Collision detection 
 *      system from
 *
 */

void ICollide::addFixedBoxes(vector<Character*> characters)
{

    // Hold the current box being created
    FixedSizeBoundingBox* fb = NULL;
    vector<Character*>::iterator itr = characters.begin();

    // Add all characters to the vector of bounding boxes
    while(itr != characters.end())
    {

        fb = new FixedSizeBoundingBox(*itr);
        m_boxes.push_back(fb);

        ++itr;

    }

    addBoxesEndPoints(m_boxes);

}

//**********************************************************
/** 
 *   Draw all bounding cubes
 */

void ICollide::drawBoundingBoxes()
{

    vector<AxisAlignedBoundingBox*>::iterator itr;
    itr = m_boxes.begin();

    while(itr != m_boxes.end())
    {

        (*itr)->draw();
        ++itr;

    }
}

//**********************************************************
/** 
 *   Draw all bounding cubes and meshes.
 *
 *   @param boxes if drawing boxes or not
 */

void ICollide::drawBoundingBoxesAndMeshes(bool boxes)
{
}


