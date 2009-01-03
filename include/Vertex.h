/* vim: set filetype=cpp.doxygen : */

#ifndef VERTEX_H_
#define VERTEX_H_

#include <Vertex2D.h>
#include <math.h>

class Vertex : public Vertex2D
{
	public:
		//---------------------------------------------
		// The member data
		//---------------------------------------------
		/* vector components */
		// int x;
		/* vector components */
		// int y;
		/* vector components */
		int z;
		
		Vertex(int x, int y, int z);
		Vertex(int* v);
		Vertex();
		
		int distanceBetween(Vertex v);
};

#endif /*VERTEX_H_*/
