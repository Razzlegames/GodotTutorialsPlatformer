#include <Vertex.h>
#include <Vertex2D.h>
#include <math.h>

//*********************************************************

Vertex::Vertex(int x, int y, int z):Vertex2D(x,y)
{

}

//*********************************************************

Vertex::Vertex():Vertex2D(0,0)
{

    this->z = 0.0f;

}


//**********************************************************
/**
 * 	@param v vector (array of 3 ints)
 */

Vertex::Vertex(int* v)
{

    this->x = v[0];
    this->y = v[1];
    this->z = v[2];

}


//**********************************************************
/**
 *   Distance between two Verticies
 */

int Vertex::distanceBetween(Vertex v)
{

    return (int)sqrt(distanceBetweenSquared(v));

}


//**********************************************************
/**
 *   Distance between Verticies Squared
 */

int Vertex::distanceBetweenSquared(Vertex v)
{

    int x_c = x - v.x;
    int y_c = y - v.y;
    int z_c = z - v.z;

    return (int)(x_c*x_c + y_c*y_c + z_c*z_c);

}

