#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(const sf::Texture& texture, sf::Vector2f pos, float speed);
    void chase(sf::Vector2f target, float dt);
private:
    float speed;
};
