#pragma once

#include <SFML/Graphics.hpp>

class Coin {
public:
    Coin(sf::Vector2f pos, float radius);

    void draw(sf::RenderWindow &window) const;
    float getRadius() const;
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape coin;
    float radius;
};
