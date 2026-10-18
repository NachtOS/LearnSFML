#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(float radius, sf::Vector2f startPos, float speed);
    void update(float dt, sf::Vector2f bounds) override;

private:
    float speed;
};
