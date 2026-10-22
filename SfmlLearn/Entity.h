#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(const sf::Texture& texture, sf::Vector2f pos, float size, float hitRadius);

    void draw(sf::RenderWindow& window) const;
    virtual void update(float dt, sf::Vector2f bounds) {}
    float getRadius() const;
    bool collidesWith(const Entity& other) const;
    sf::Vector2f getPosition() const;

    virtual ~Entity() = default;
protected:
    sf::Sprite sprite;
    float radius;

    void setFrame(sf::IntRect rect, float size);
};
