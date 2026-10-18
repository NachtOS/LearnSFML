#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(float radius, sf::Color color, sf::Vector2f pos);

    void draw(sf::RenderWindow& window) const;
    float getRadius() const;
    bool collidesWith(const Entity& other) const;
    sf::Vector2f getPosition() const;

    virtual ~Entity() = default;
protected:
    sf::CircleShape entity;
    float radius;
};
