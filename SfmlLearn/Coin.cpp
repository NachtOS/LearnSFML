#include "Coin.h"

Coin::Coin(float radius, sf::Vector2f pos)
    : Entity(radius, sf::Color(227, 223, 18), pos) {}

void Coin::onTouch(int& score, int& /*lives*/) {
    ++score;
}
