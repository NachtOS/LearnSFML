#include "Entity.h"

Entity::Entity(float radius, sf::Color color, sf::Vector2f pos)
    : entity(radius), radius(radius) {
    entity.setFillColor(color);
    entity.setOrigin({radius, radius});
    entity.setPosition(pos);
}

void Entity::draw(sf::RenderWindow &window) const {
    window.draw(entity);
}

void Entity::setTexure(const sf::Texture &texture) {
    entity.setTexture(&texture);
    entity.setFillColor(sf::Color::White);
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
    return entity.getPosition();
}
