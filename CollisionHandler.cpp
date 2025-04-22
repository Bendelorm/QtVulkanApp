#include "Renderer.h"
#include "CollisionHandler.h"


CollisionHandler::CollisionHandler(Renderer& renderer) : mRenderer(renderer)
{

}
QVector3D CollisionHandler::vectorBetween(const VisualObject &a, const VisualObject &b)
{
    return a.Position - b.Position;  // Vector from A to B
}
void CollisionHandler::handleCollision(VisualObject &a, VisualObject &b)
{
    if (b.getName() == "quad")
    {
        qDebug("collected");
        b.move(0, 100, 0);
    }
}
void CollisionHandler::checkCollision()
{
    std::vector<VisualObject*>& Objects = mRenderer.getObjects(); //Returns mObjects

    //qDebug("I work");

    // Check if there are any objects in the list
    if (Objects.empty())
    {
        qDebug() << "No objects on the map to check!";
    }
    for (size_t i = 0; i < Objects.size(); ++i)
    {
        if(i == 3)
        {
            continue;
        }
        else if (vectorBetween(*Objects.at(3), *Objects.at(i)).length() < Objects.at(3)->Radius + Objects.at(i)->Radius)
        {
            handleCollision(*Objects.at(3), *Objects.at(i));
        }
    }
}
