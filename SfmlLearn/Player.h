#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float radius, sf::Vector2f startPos, float speed);

    void update(float dt, sf::Vector2f bounds);
    void draw(sf::RenderWindow& window) const;
    float getRadius() const;
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape;
    float radius;
    float speed;
};