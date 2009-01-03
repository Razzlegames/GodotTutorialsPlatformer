/* vim: set filetype=cpp.doxygen : */

#ifndef VERTEX2D_
#define VERTEX2D_

class Vertex2D
{
	public:
		//---------------------------------------------
		// The member data
		//---------------------------------------------
		/* vector components */
		int x;
		/* vector components */
		int y;

		Vertex2D();
        Vertex2D(int* v);
		Vertex2D(int x, int y);
};
#endif /*VERTEX2D_*/
