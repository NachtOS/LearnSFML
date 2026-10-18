#pragma once

#include <SFML/Graphics.hpp>
// radius и entity находятся в protected потому что их должны видеть дочерние классы
class Entity {
public:
    Entity(float radius, sf::Color color, sf::Vector2f pos);

    void draw(sf::RenderWindow& window) const;
    void setTexture(const sf::Texture &texture);
    virtual void update(float dt, sf::Vector2f bounds) {}
    float getRadius() const;
    bool collidesWith(const Entity& other) const;
    sf::Vector2f getPosition() const;

    virtual ~Entity() = default;
protected:
    sf::CircleShape entity;
    float radius;
};
