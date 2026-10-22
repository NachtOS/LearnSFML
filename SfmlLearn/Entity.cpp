#include "Entity.h"

Entity::Entity(const sf::Texture& texture, sf::Vector2f pos, float size, float hitRadius)
    : sprite(texture), radius(hitRadius) {
    sprite.setOrigin({radius, radius});
    sprite.setPosition(pos);
}

void Entity::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}

float Entity::getRadius() const {
    return radius;
}

bool Entity::collidesWith(const Entity &other) const {
    float dx = getPosition().x - other.getPosition().x;
    float dy = getPosition().y - other.getPosition().y;
    float r  = radius + other.getRadius();

    return dx * dx + dy * dy < r * r;
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}
