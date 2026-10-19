#pragma once

#include "Entity.h"

class Coin : public Entity {
public:
    Coin(float radius, sf::Vector2f pos, const sf::Texture& texture);
};
