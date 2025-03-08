#include "TriangleSurface.h"
#include <fstream>
#include <QDebug>
TriangleSurface::TriangleSurface() : VisualObject()
{
    Vertex v1{-20.0f,   0.0f,  20.0f,   0.0f, 0.3f, 0.0f, 0.0f, 0.0f};
    Vertex v2{20.0f,   0.0f,  -20.0f,   0.0f, 0.3f, 0.0f, 0.0f, 0.0f};
    Vertex v3{20.0f,   0.0f,  20.0f,   0.0f, 0.3f, 0.0f, 0.0f, 0.0f};
    Vertex v4{-20.0f,   0.0f,  -20.0f,   0.0f, 0.3f, 0.0f, 0.0f, 0.0f};

    //Pushing 1st triangle,
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);
    //then the 2nd.
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v4);

    //Temporary scale and positioning
    //mMatrix.scale(0.0f);
    mMatrix.translate(0.0f, 0.0f, 0.0f);
}

TriangleSurface::TriangleSurface(const std::string &filename)
{
    std::ifstream inn(filename);
    if (!inn.is_open())
        return;
    // read input from math part of compulsory
    int n;
    Vertex v;
    inn >> n;
    for (auto i=0; i<n; i++)
    {
        inn >> v;
        mVertices.push_back(v);
        //qDebug() << v.x << v.y << v.z;
    }
    inn.close();
}
