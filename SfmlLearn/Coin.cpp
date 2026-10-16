#include "Coin.h"

Coin::Coin(sf::Vector2f pos, float radius)
    : coin(radius), radius(radius){
    coin.setFillColor(sf::Color(227, 223, 18));
    coin.setOrigin({radius, radius});
    coin.setPosition(pos);
}

void Coin::draw(sf::RenderWindow &window) const {
    window.draw(coin);
}

float Coin::getRadius() const {
    return radius;
}

sf::Vector2f Coin::getPosition() const {
    return coin.getPosition();
}
