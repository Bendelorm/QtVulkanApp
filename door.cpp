#include "door.h"

Door::Door()
{
    Vertex v1{0.0f,   0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f};
    Vertex v2{0.0f,   4.0f,  1.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f};
    Vertex v3{0.0f,   0.0f,  -1.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f};
    Vertex v4{0.0f,   4.0f,  -1.0f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f};
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);

    mVertices.push_back(v2);
    mVertices.push_back(v3);
    mVertices.push_back(v4);
}
