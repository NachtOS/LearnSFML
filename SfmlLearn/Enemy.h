#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(sf::Vector2f pos, sf::Vector2f velocity, float radius, const sf::Texture& texture);
    void update(float dt, sf::Vector2f bounds) override;
private:
    sf::Vector2f velocity;
};
