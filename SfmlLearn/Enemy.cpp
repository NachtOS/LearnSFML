#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f velocity, float radius, const sf::Texture& texture)
    : Entity(radius, sf::Color::White, pos), velocity(velocity) {
    entity.setTexture(&texture);
}

void Enemy::update(float dt, sf::Vector2f bounds) {
    entity.move(velocity * dt);

    sf::Vector2f pos = entity.getPosition();
    if (pos.x < radius) {
        pos.x = radius;
        velocity.x = -velocity.x;
    }
    if (pos.x > bounds.x - radius) {
        pos.x = bounds.x - radius;
        velocity.x = -velocity.x;
    }
    if (pos.y < radius) {
        pos.y = radius;
        velocity.y = -velocity.y;
    }
    if (pos.y > bounds.y - radius) {
        pos.y = bounds.y - radius;
        velocity.y = -velocity.y;
    }

    entity.setPosition(pos);
}
