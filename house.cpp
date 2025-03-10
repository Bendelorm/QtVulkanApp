#include "house.h"

House::House()
{
    Vertex v1{-4.0f,   0.0f,  -4.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v2{-4.0f,   10.0f,  -4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v3{4.0f,   0.0f,  -4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v4{4.0f,   10.0f,  -4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v5{-4.0f,   0.0f,  4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v6{-4.0f,   10.0f,  4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v7{4.0f,   0.0f,  4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    Vertex v8{4.0f,   10.0f,  4.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f};


    //Pushing triangles to create box
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);

    mVertices.push_back(v2);
    mVertices.push_back(v3);
    mVertices.push_back(v4);

    //2. surface
    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v5);

    mVertices.push_back(v2);
    mVertices.push_back(v5);
    mVertices.push_back(v6);

    //3. surface

    mVertices.push_back(v5);
    mVertices.push_back(v6);
    mVertices.push_back(v7);

    mVertices.push_back(v6);
    mVertices.push_back(v7);
    mVertices.push_back(v8);

    //4. surface
    mVertices.push_back(v7);
    mVertices.push_back(v8);
    mVertices.push_back(v3);

    mVertices.push_back(v8);
    mVertices.push_back(v3);
    mVertices.push_back(v4);

    //roof
    mVertices.push_back(v2);
    mVertices.push_back(v4);
    mVertices.push_back(v6);

    mVertices.push_back(v4);
    mVertices.push_back(v6);
    mVertices.push_back(v8);

    //floor
    mVertices.push_back(v1);
    mVertices.push_back(v3);
    mVertices.push_back(v5);

    mVertices.push_back(v3);
    mVertices.push_back(v5);
    mVertices.push_back(v7);

}
