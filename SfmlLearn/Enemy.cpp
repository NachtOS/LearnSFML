#include <cmath>

#include "Enemy.h"

Enemy::Enemy(const sf::Texture& runTex, sf::Vector2f pos, float speed, float size)
    : Entity(runTex, pos, size, 18.f), runTexture(&runTex), frameSize(96, 64), runFrames(10),
    frameCount(runFrames), frameTime(0.08f), speed(speed) {
    setFrame(sf::IntRect({0, 0}, frameSize), size);
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f toTarget = target - sprite.getPosition();
    if (toTarget.length() > 0.f) {
        // normalized() делает вектор длиной 1, чтобы враг шёл с одной скоростью, неважно, далеко игрок или близко
        sf::Vector2f dir = toTarget.normalized();
        sprite.move(dir * speed * dt);

        if (target.x < sprite.getPosition().x) {
            sprite.setScale({-std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
        }
        if (target.x > sprite.getPosition().x) {
            sprite.setScale({std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
        }
    }

    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        frame = (frame + 1) % frameCount;
    }
    sprite.setTextureRect(sf::IntRect({frame * frameSize.x, 0}, frameSize));
}
