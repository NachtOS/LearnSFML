#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, float speed, float radius, const sf::Texture& texture)
    : Entity(radius, sf::Color::White, pos), speed(speed) {
    entity.setTexture(&texture);
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f toTarget = target - entity.getPosition();
    if (toTarget.length() > 0.f) {
        // normalized() делает вектор длиной 1, чтобы враг шёл с одной скоростью, неважно, далеко игрок или близко
        sf::Vector2f dir = toTarget.normalized();
        entity.move(dir * speed * dt);
    }
}
