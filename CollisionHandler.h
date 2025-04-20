#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H
#include "VisualObject.h"

class Renderer;
class CollisionHandler
{
public:
    CollisionHandler(Renderer& renderer);

    QVector3D vectorBetween(const VisualObject& a, const VisualObject& b);
    void handleCollision(VisualObject& a, VisualObject& b);
    void checkCollision();

private:
    Renderer& mRenderer;
};

#endif // COLLISIONHANDLER_H
