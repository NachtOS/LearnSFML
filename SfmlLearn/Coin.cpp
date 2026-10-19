#include "Coin.h"

Coin::Coin(float radius, sf::Vector2f pos, const sf::Texture& texture)
    : Entity(radius, sf::Color::White, pos) {
    entity.setTexture(&texture);
}