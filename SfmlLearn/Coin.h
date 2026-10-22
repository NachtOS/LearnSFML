#pragma once

#include "Entity.h"

class Coin : public Entity {
public:
    Coin(const sf::Texture& texture, sf::Vector2f pos);
};
