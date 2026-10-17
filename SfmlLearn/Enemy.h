#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(sf::Vector2f pos, sf::Vector2f velocity, float radius);

    void draw(sf::RenderWindow &window) const;
    void update(float dt, sf::Vector2f bounds);
    float getRadius() const;
    sf::Vector2f getPosition() const;
private:
    sf::CircleShape enemy;
    sf::Vector2f velocity;
    float radius;
};
