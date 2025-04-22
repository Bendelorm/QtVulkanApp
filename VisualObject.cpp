#include "VisualObject.h"

VisualObject::~VisualObject()
{
    mMatrix.setToIdentity();
}

void VisualObject::move(float x, float y, float z)
{

    Position += QVector3D(x, y, z);

    // After moving, update the matrix with the new position and yaw
    updateMatrix();

    qDebug() << "Stored Position: (" << Position.x() << ", " << Position.y() << ", " << Position.z() << ")";
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::rotate(float t, float x, float y, float z)
{
    if (x == 0.f && y == 1.f && z == 0.f)
    {
        mYaw += t; // Update yaw when rotating around Y-axis
    }
    updateMatrix();
}
QVector3D VisualObject::getForward() const
{
    float radians = qDegreesToRadians(mYaw);
    return QVector3D(qSin(radians), 0.f, qCos(radians)).normalized();
}


float VisualObject::getYaw() const
{
    return mYaw;
}
void VisualObject::updateMatrix()
{
    QMatrix4x4 mat;
    mat.translate(Position);
    mat.rotate(mYaw, 0.f, 1.f, 0.f); // yaw only
    mMatrix = mat;
}
