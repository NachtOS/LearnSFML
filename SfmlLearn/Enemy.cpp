#include "Enemy.h"

Enemy::Enemy(const sf::Texture& texture, sf::Vector2f pos, float speed)
    : Entity(texture, pos, 60.f, 18.f), speed(speed) {}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f toTarget = target - sprite.getPosition();
    if (toTarget.length() > 0.f) {
        // normalized() делает вектор длиной 1, чтобы враг шёл с одной скоростью, неважно, далеко игрок или близко
        sf::Vector2f dir = toTarget.normalized();
        sprite.move(dir * speed * dt);
    }
}
