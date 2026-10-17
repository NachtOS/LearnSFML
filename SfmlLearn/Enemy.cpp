#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f velocity, float radius)
    : enemy(radius), velocity(velocity), radius(radius) {
    enemy.setFillColor(sf::Color(194, 39, 25));
    enemy.setOrigin({radius, radius});
    enemy.setPosition(pos);
}

void Enemy::update(float dt, sf::Vector2f bounds) {
    enemy.move(velocity * dt);

    sf::Vector2f pos = enemy.getPosition();
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

    enemy.setPosition(pos);
}

void Enemy::draw(sf::RenderWindow &window) const {
    window.draw(enemy);
}

float Enemy::getRadius() const {
    return radius;
}

sf::Vector2f Enemy::getPosition() const {
    return enemy.getPosition();
}
