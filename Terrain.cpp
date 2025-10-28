#include "Terrain.h"
#include <QDebug>
#include <cmath>

Terrain::Terrain() : VisualObject()
{
    drawType = 0; // 0 = fill, 1 = wireframe


    const int xCount = 5;
    const int zCount = 3;
    const float xStep = 1.0f;
    const float zStep = 1.0f;

    auto heightFunc = [](float x) {
        float dx = (x - 2.0f);
        return 0.6f * dx * dx * 0.25f;
    };

    for (int z = 0; z < zCount; ++z) {
        for (int x = 0; x < xCount; ++x) {
            float xf = x * xStep;
            float zf = z * zStep;
            float yf = heightFunc(xf);
            mVertices.push_back({xf, yf, zf,  // position
                                 0.2f + 0.2f*x, 0.4f, 1.0f - 0.1f*z,
                                 x / float(xCount - 1), z / float(zCount - 1)});
        }
    }

    for (int z = 0; z < zCount - 1; ++z) {
        for (int x = 0; x < xCount - 1; ++x) {
            int i0 = z * xCount + x;
            int i1 = i0 + 1;
            int i2 = i0 + xCount;
            int i3 = i2 + 1;

            mTriangles.push_back({{i0, i1, i2}, {-1,-1,-1}});
            mTriangles.push_back({{i1, i3, i2}, {-1,-1,-1}});

            mIndices.push_back(i0);
            mIndices.push_back(i1);
            mIndices.push_back(i2);

            mIndices.push_back(i1);
            mIndices.push_back(i3);
            mIndices.push_back(i2);
        }
    }

    float startX = 0.2f;
    float startZ = 1.0f;
    float startY = getHeightAt(startX, startZ) + 0.1f;
    mBallPos = QVector3D(startX, startY, startZ);
    mBallVel = QVector3D(0.3f, 0.0f, 0.0f); // slight push toward center

    qDebug() << "Ball starts at" << mBallPos;

    mMatrix.setToIdentity();
}

QVector3D Terrain::computeTriangleNormal(const Triangle& tri) const
{
    const QVector3D p0(mVertices[tri.v[0]].x, mVertices[tri.v[0]].y, mVertices[tri.v[0]].z);
    const QVector3D p1(mVertices[tri.v[1]].x, mVertices[tri.v[1]].y, mVertices[tri.v[1]].z);
    const QVector3D p2(mVertices[tri.v[2]].x, mVertices[tri.v[2]].y, mVertices[tri.v[2]].z);
    return QVector3D::crossProduct(p1 - p0, p2 - p0).normalized();
}

int Terrain::findContainingTriangle(const QVector3D& pos) const
{
    int best = 0;
    float bestDist = 1e9f;
    for (int i = 0; i < (int)mTriangles.size(); ++i) {
        const QVector3D p0(mVertices[mTriangles[i].v[0]].x, mVertices[mTriangles[i].v[0]].y, mVertices[mTriangles[i].v[0]].z);
        const QVector3D p1(mVertices[mTriangles[i].v[1]].x, mVertices[mTriangles[i].v[1]].y, mVertices[mTriangles[i].v[1]].z);
        const QVector3D p2(mVertices[mTriangles[i].v[2]].x, mVertices[mTriangles[i].v[2]].y, mVertices[mTriangles[i].v[2]].z);

        QVector3D center = (p0 + p1 + p2) / 3.0f;
        float dist = (QVector2D(center.x(), center.z()) - QVector2D(pos.x(), pos.z())).lengthSquared();

        if (dist < bestDist) {
            bestDist = dist;
            best = i;
        }
    }
    return best;
}

float Terrain::getHeightAt(float x, float z) const
{
    int triIndex = findContainingTriangle(QVector3D(x, 0.0f, z));
    if (triIndex < 0 || triIndex >= mTriangles.size())
        return 0.0f;

    const Triangle& tri = mTriangles[triIndex];
    const Vertex& v0 = mVertices[tri.v[0]];
    const Vertex& v1 = mVertices[tri.v[1]];
    const Vertex& v2 = mVertices[tri.v[2]];

    QVector3D p0(v0.x, v0.y, v0.z);
    QVector3D p1(v1.x, v1.y, v1.z);
    QVector3D p2(v2.x, v2.y, v2.z);

    QVector3D n = QVector3D::crossProduct(p1 - p0, p2 - p0);
    if (fabs(n.y()) < 1e-6f)
        return p0.y();

    float a = -n.x() / n.y();
    float b = -n.z() / n.y();
    float c = (n.x() * p0.x() + n.y() * p0.y() + n.z() * p0.z()) / n.y();

    return a * x + b * z + c;
}

void Terrain::simulateBall(float dt)
{
    if (mTriangles.empty() || mVertices.empty())
        return;

    QVector3D gravityVec(0.0f, -mGravity, 0.0f);

    int triIndex = findContainingTriangle(mBallPos);
    QVector3D normal = computeTriangleNormal(mTriangles[triIndex]);

    QVector3D tangent = gravityVec - QVector3D::dotProduct(gravityVec, normal) * normal;
    QVector3D acc = tangent;

    mBallVel += acc * dt;
    mBallPos += mBallVel * dt;

    float groundY = getHeightAt(mBallPos.x(), mBallPos.z());
    float ballRadius = 0.15f;

    if (mBallPos.y() < groundY + ballRadius)
    {
        mBallPos.setY(groundY + ballRadius);
        if (mBallVel.y() < 0.0f)
            mBallVel.setY(-mBallVel.y() * 0.2f);
        mBallVel *= 0.99f; // friction
    }
}
