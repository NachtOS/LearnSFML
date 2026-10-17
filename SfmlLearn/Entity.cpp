#include "Entity.h"

Entity::Entity(float radius, sf::Color color, sf::Vector2f pos)
    : radius(radius), entity(radius) {
    entity.setFillColor(sf::Color(color));
    entity.setOrigin({radius, radius});
    entity.setPosition(pos);
}

void Entity::draw(sf::RenderWindow &window) const {
    window.draw(entity);
}

float Entity::getRadius() const {
    return radius;
}
