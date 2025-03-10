#ifndef ENEMY_H
#define ENEMY_H

#include "VisualObject.h"

class Enemy : public VisualObject
{
public:
    Enemy();
    void setSpeed(float speed);
    void moveRight(float delta);
    void update(float deltaTime);

private:
    float Speed = 10.0f;   // Movement speed
    int Direction = 1;    // 1 = forward, -1 = backward
    float LeftLimit = -15.0f;  // Left boundary
    float RightLimit = 15.0f; // Right boundary
};

#endif // ENEMY_H
