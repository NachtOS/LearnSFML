#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(sf::Vector2f pos, sf::Vector2f velocity, float radius);
    void update(float dt, sf::Vector2f bounds) override;
    void onTouch(int& score, int& lives) override;
private:
    sf::Vector2f velocity;
};
