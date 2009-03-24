#include <Vertex2D.h>
#include <math.h>

Vertex2D::Vertex2D():
    x(0),
    y(0)
{

}

Vertex2D::Vertex2D(int x, int y):
    x(x),
    y(y)
{

}

Vertex2D::Vertex2D(int* v)
{
    x = v[0];
    y=v[1];
}

