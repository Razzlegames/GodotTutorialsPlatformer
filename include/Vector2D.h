/* vim: set filetype=cpp.doxygen : */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

//#include <OpenEXR/ImathVec.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cassert>

//const int M_180_OVER_PI = (180/M_PI);
//const int M_PI_OVER_180 = (M_PI/180);

/*
__attribute__((aligned(4))) typedef struct Face_
{
	Vector2D* v1; Vector2D* v2; Vector2D* v3;
}Face;
*/
//typedef vector<Face> FaceList;
/*
typedef struct Polygon_
{
	FaceList faces_list;
}Polygon;
*/

/**
 *   Represent a 2D Vector
 */
class Vector2D 
{

  public:


      static const enum {
          X_CORD=0,Y_CORD=1,Z_CORD=2}cords;

      //---------------------------------------------
      // The member data
      //---------------------------------------------

      /// vector components 
      int x;

      /// vector components 
      int y;

      //---------------------------------------------
      // Constructors / Destructor
      //---------------------------------------------

      Vector2D();
      Vector2D(int x, int y);
      Vector2D(int* v);
      virtual ~Vector2D();

      //---------------------------------------------
      // Operators
      //---------------------------------------------

      Vector2D operator+ (const Vector2D);
      Vector2D  operator- (const Vector2D v2);
      Vector2D  operator- (void);
      int operator^ (const Vector2D v2);
      int dot (const Vector2D v2);
      Vector2D  operator% (const Vector2D v2);
      Vector2D  operator/ (const int n);
      Vector2D  operator/= (const int n);
      Vector2D operator* (const int s);
      bool operator== (const Vector2D v);
      bool operator!= (const Vector2D v);
      void operator+= (const Vector2D v2);
      void operator-= (const Vector2D v2);

      // Array like access to attributes (for convenience)
      int& operator[](int i);

      //---------------------------------------------
      //   Member Functions
      //---------------------------------------------
      int angleInDegree(const Vector2D v1);
      void printVector();
      int magnitude();
      int magnitudeSquared();

      //  Same as magnitude
      int length();

      // Normalize to legnth 1 vector
      Vector2D normalize();

      //void normalizeToint(int* n);

      bool equal(const Vector2D v);
      bool equalApprox(const Vector2D v);
      int& getCord(unsigned int i);

};

inline int Vector2D::length()
{

    return magnitude();

}

#endif /*Vector2D_H_*/
