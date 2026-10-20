#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(sf::Vector2f pos, float speed, float radius, const sf::Texture& texture);
    void chase(sf::Vector2f target, float dt);
private:
    float speed;
};
