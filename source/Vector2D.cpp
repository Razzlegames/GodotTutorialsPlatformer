#include <Vector2D.h>

Vector2D::Vector2D()
{

	x=0;y=0;

}

//**********************************************************
/**
 *   \param x cord
 *   \param y cord
 * 	 \param z cord
 */

Vector2D::Vector2D(int x, int y):Vertex2D(x,y)
{

	//this->x = x;
	//this->y = y;
	//this->z = z;
}

//**********************************************************
/**
 * 	\param v vector (array of 3 ints)
 */

Vector2D::Vector2D(int* v):Vertex2D(v)
{

}

//**********************************************************

Vector2D::~Vector2D()
{
}

//**********************************************************
/**
 * 	Create a vector from 2 verticies
 * 		@param v1 point where vector starts
 * 		@param v2 point where vector ends
 */

Vector2D::Vector2D(Vertex2D v1, Vertex2D v2):Vertex2D()
{

	this->x = v2.x-v1.x;
	this->y = v2.y-v1.y;
}

//**********************************************************

bool Vector2D::equal(const Vector2D v)
{


	return (x == v.x && y == v.y);
}

//**********************************************************

bool Vector2D::operator==(const Vector2D v)
{


	return (x == v.x && y == v.y);
}

//**********************************************************
/**
 *   Check to see if an Vector2D exists in a vector<Vector2D>
 * 	(e.g.  to see if two verticies match)
 * 		@param index vector to check
 * 		@param a integer to look for
 * 			@return  -1 if not found, else place where found
 */
/*

int Vector2D::existsApprox(vector<Vector2D> index, Vector2D a)
{

	for(int i = 0; i < index.size();i++)
	{

		if(index[i].equalApprox(a))
		{

			return i;
		}

	}

	return -1;
}

*/
//**********************************************************
/**
 * 		Seemless adding of vectors
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new vector
 */

Vector2D  Vector2D::operator+ (const Vector2D v2)
{

	return Vector2D(x+v2.x, y+v2.y);
}

//**********************************************************
/**
 * 		Seemless adding of vectors
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new vector
 */

void  Vector2D::operator+= (const Vector2D v2)
{

	const Vector2D v1 = *(this);
	*this = Vector2D(v1.x+v2.x, v1.y+v2.y);
}

//**********************************************************
/**
 * 		Seemless adding of vectors
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new vector
 */

void  Vector2D::operator-= (const Vector2D v2)
{

	*this = Vector2D(x-v2.x, y-v2.y);
}

//**********************************************************
/**
 * 		Seemless subtraction of vectors
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new vector
 */

Vector2D  Vector2D::operator- (const Vector2D v2)
{

	const Vector2D v1 = *(this);
	return Vector2D(v1.x-v2.x, v1.y-v2.y);
}

//**********************************************************
/**
 * 		Seemless negation of vector
 * 		\return new vector
 */

Vector2D  Vector2D::operator- ()
{

	const Vector2D v1 = *(this);
	return Vector2D(-v1.x, -v1.y);
}

//**********************************************************
/**
 * 		Seemless mult of vector with scalar
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new vector scaled by s
 */

Vector2D Vector2D::operator* (const int s)
{

	return Vector2D(x*s,y*s);
}

//**********************************************************
/**
 * 		Seemless dot product of vectors
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new int based on dot product of both vectors
 */

int  Vector2D::operator^ (const Vector2D v2)
{

	const Vector2D v1 = *(this);
	return v1.x*v2.x+ v1.y*v2.y;
}


//**********************************************************
/**
 * 		Seemless cross product of vectors
 * 			\param v1 first to add
 * 			\param v2 second
 * 		\return new int based on dot product of both vectors
 */

Vector2D  Vector2D::operator% (const Vector2D v1)
{

	const Vector2D v2 = *(this);

        // Here is our good ol' cross product determinate
        return Vector2D(v1.y-v2.y   /* ^x */,
                -(v1.x-v2.x)/* ^y */
                );
}

//**********************************************************
/**
 *      FIX!!!
 * 		Seemless angle between 2 vectors
 * 		(Will be doing normalization on both to avoid
 * 	NOT-A-NUMBER issues with trigonometry, e.g. acos(n),n>1||n<-1)
 * 			\param v1
 * 		\return new int based on dot product of both vectors
 */

int Vector2D::angleInDegree(const Vector2D v1)
{

	Vector2D temp = v1;
	//printf("v2 ^ v1: %f\n",normalize() ^ temp.normalize());
	//printf("acos(v2 ^ v1): %f\n",acos(normalize() ^ temp.normalize()));
	// Here is our good ol' cross product determinate
        
	//return M_180_OVER_PI*acos(normalize() ^ temp.normalize());
        return 0;
}

//************************************************************
/**
 *   Normalize the vector and save to a int
 */

//void Vector2D::normalizeToint(int* n)
//{
//
//	normalize().tointArray(n);
//}

//************************************************************

Vector2D Vector2D::normalize()
{

	int mag = (int)magnitude();

	// Div by zero is bad, M'Kay
	if(mag != 0)
		return (*this)/ mag;
	else
		return *this;
}

//************************************************************

int Vector2D::magnitude()
{


	return (int)sqrt(x*x + y*y);

}

//************************************************************
/**
 * 	 Scalar division of vector by n
 */

Vector2D  Vector2D::operator/ (int n)
{


	return Vector2D(x/n, y/n);

}

//************************************************************
/**
 * 	 Scalar division of vector by n
 */

Vector2D  Vector2D::operator/= (const int n)
{

	x /= n;
	y /= n;
	return *this;

}

//**********************************************************

void Vector2D::printVector()
{


	//cout << "{" << x <<", "<<  y <<", " << z <<"} "<<endl;

}

