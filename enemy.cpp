#include "enemy.h"

Enemy::Enemy()
{
Vertex v1{0.0f,   0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v2{0.0f,   1.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v3{1.0f,   0.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v4{1.0f,   1.0f,  0.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v5{0.0f,   0.0f,  1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v6{0.0f,   1.0f,  1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v7{1.0f,   0.0f,  1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
Vertex v8{1.0f,   1.0f,  1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f};


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
