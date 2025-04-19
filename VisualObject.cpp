#include "VisualObject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
}

void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    Position.setX(mMatrix(0, 3));
    Position.setY(mMatrix(1, 3));
    Position.setZ(mMatrix(2, 3));
    qDebug() << "Stored Position: (" << Position.x() << ", " << Position.y() << ", " << Position.z() << ")";
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::rotate(float t, float x, float y, float z)
{
    mMatrix.rotate(t, x, y, z);
}
