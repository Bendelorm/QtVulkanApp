#ifndef PLAYER_H
#define PLAYER_H
#include "VisualObject.h"

class Player : public VisualObject
{
public:
    Player();
    void setSpeed(float speed);
    void moveRight(float delta);
};

#endif // PLAYER_H
