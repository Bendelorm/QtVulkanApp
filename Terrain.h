#pragma once
#include "VisualObject.h"
#include <vector>
#include <QVector3D>

struct Triangle {
    int v[3];      // Indekser til mVertices
    int neighbors[3]; // Nabotrekanter (−1 hvis ingen)
};

class Terrain : public VisualObject
{
public:
    Terrain();

    // Simulerer ball som sklir i retning av gravitasjonen (Newtons 2. lov)
    void simulateBall(float dt);
    float getHeightAt(float x, float z) const;
    QVector3D getBallPosition() const { return mBallPos; }

private:
    std::vector<Triangle> mTriangles;

    QVector3D mBallPos;
    QVector3D mBallVel;
    float mBallMass = 1.0f;
    float mGravity = 9.81f;

    // Hjelpefunksjoner
    QVector3D computeTriangleNormal(const Triangle& tri) const;
    int findContainingTriangle(const QVector3D& pos) const;
};
