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
 * 	\param v vector (array of 3 ints)
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
	return sqrt(pow((x-v.x),2) + pow(y-v.y,2) + pow(z-v.z,2));
}
