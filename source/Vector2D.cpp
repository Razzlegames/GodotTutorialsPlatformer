#include <Vector2D.h>

//**********************************************************

Vector2D::Vector2D():
    x(0),
    y(0)
{

}

//**********************************************************
/**
 *   @param x cord
 *   @param y cord
 *   @param z cord
 */

Vector2D::Vector2D(int x, int y):
    x(x),
    y(y)
{

}

//**********************************************************
/**
 *   @param v vector (array of 3 ints)
 */

Vector2D::Vector2D(int* v)
{

    x = v[0];
    y = v[1];

}

//**********************************************************

Vector2D::~Vector2D()
{

}

//**********************************************************

bool Vector2D::equal(const Vector2D v)
{

    return (x == v.x && y == v.y);

}

//**********************************************************
/**
 *   Test equality of two vectors
 */

bool Vector2D::operator==(const Vector2D v)
{

    return equal(v);

}

//**********************************************************
/**
 *   Test inequality of two vectors
 */

bool Vector2D::operator!=(const Vector2D v)
{

    return !equal(v);

}


//**********************************************************
/**
 * 		 adding of vectors
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new vector
 */

Vector2D  Vector2D::operator+ (const Vector2D v2)
{

    return Vector2D(x+v2.x, y+v2.y);

}

//**********************************************************
/**
 * 		 adding of vectors
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new vector
 */

void  Vector2D::operator+= (const Vector2D v2)
{

    const Vector2D v1 = *(this);
    *this = Vector2D(v1.x+v2.x, v1.y+v2.y);
}

//**********************************************************
/**
 * 		 adding of vectors
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new vector
 */

void  Vector2D::operator-= (const Vector2D v2)
{

    *this = Vector2D(x-v2.x, y-v2.y);
}

//**********************************************************
/**
 *     subtraction of vectors
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new vector
 */

Vector2D  Vector2D::operator- (const Vector2D v2)
{

    return Vector2D(x-v2.x, y-v2.y);
}

//**********************************************************
/**
 * 		 negation of vector
 * 		@return new vector
 */

Vector2D  Vector2D::operator- ()
{

    return Vector2D(-x, -y);

}

//**********************************************************
/**
 * 		 mult of vector with scalar
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new vector scaled by s
 */

Vector2D Vector2D::operator* (const int s)
{

    return Vector2D(x*s,y*s);

}

//**********************************************************
/**
 * 	 dot product of vectors
 *
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new int based on dot product of both vectors
 */

int  Vector2D::operator^ (const Vector2D v2)
{

    return dot(v2);

}

//**********************************************************
/**
 *    dot product of vectors
 *
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new int based on dot product of both vectors
 */

int  Vector2D::dot(const Vector2D v2)
{

    return x*v2.x + y*v2.y;

}



//**********************************************************
/**
 * 		 cross product of vectors
 *   @param v1 first to add
 *   @param v2 second
 * 		@return new int based on dot product of both vectors
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
 * 		 angle between 2 vectors
 * 		(Will be doing normalization on both to avoid
 * 	NOT-A-NUMBER issues with trigonometry, e.g. acos(n),n>1||n<-1)
 *   @param v1
 * 		@return new int based on dot product of both vectors
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
    {

        return (*this)/ mag;
    }
    else
    {

        return *this;
    }

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

