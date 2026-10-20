#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, float speed, float radius, const sf::Texture& texture)
    : Entity(radius, sf::Color::White, pos), speed(speed) {
    entity.setTexture(&texture);
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f toTarget = target - entity.getPosition();
    if (toTarget.length() > 0.f) {
        // Деление вектора "normalized()" чтобы враг шёл с одной скоростью независимо от того как далеко игрок
        sf::Vector2f dir = toTarget.normalized();
        entity.move(dir * speed * dt);
    }
}
