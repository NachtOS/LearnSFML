#include <cmath>

#include "Enemy.h"

Enemy::Enemy(const sf::Texture& walkTex, const sf::Texture& attackTex, const sf::Texture& idleTex, sf::Vector2f pos, float speed, float size,
    float health, float damage)
    : Entity(walkTex, pos, size, 22.f), walkTexture(&walkTex), attackTexture(&attackTex), idleTexture(&idleTex),
    walkFrames(10), attackFrames(10), idleFrames(8), frameSize(96, 64), frameCount(walkFrames), frameTime(0.08f),
    speed(speed), health(health), damage(damage) {

    setFrame(sf::IntRect({0, 0}, frameSize), size);
}

void Enemy::chase(sf::Vector2f target, float dt) {
    sf::Vector2f toTarget = target - sprite.getPosition();
    EnemyState newState = EnemyState::Idle;
    if (toTarget.length() > 50.f) {
        // normalized() делает вектор длиной 1, чтобы враг шёл с одной скоростью, неважно, далеко игрок или близко
        sf::Vector2f dir = toTarget.normalized();
        sprite.move(dir * speed * dt);
        newState = EnemyState::Walk;
    }

    if (target.x < sprite.getPosition().x) {
        sprite.setScale({-std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
    }
    if (target.x > sprite.getPosition().x) {
        sprite.setScale({std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
    }

    if (cooldown > 0.f) {
        cooldown -= dt;
    }

    if (toTarget.length() <= 50.f && cooldown <= 0.f) {
        newState = EnemyState::Attack;
    }

    if (attackDone) {
        attackDone = false;
        cooldown = 1.f;
    }

    if (newState == EnemyState::Attack && frame != attackFrames) {
        newState = EnemyState::Attack;
    } else if (toTarget.length() > 50.f) {
        newState = EnemyState::Walk;
    } else if (toTarget.length() <= 50.f && cooldown <= 0.f) {
        newState = EnemyState::Attack;
    } else {
        newState = EnemyState::Idle;
    }

    if (state != newState) {
        state = newState;
        frame = 0;
        frameTimer = 0;
        switch (state) {
            case EnemyState::Walk:
                sprite.setTexture(*walkTexture);
                frameCount = walkFrames;
                break;
            case EnemyState::Attack:
                sprite.setTexture(*attackTexture);
                frameCount = attackFrames;
                break;
            default:
                if (cooldown > 0.f) {
                    sprite.setTexture(*idleTexture);
                    frameCount = idleFrames;
                }
                break;
        }
    }

    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        frame = (frame + 1) % frameCount;
        if (state == EnemyState::Attack && frame == 0) {
            attackDone = true;
        }
    }
    sprite.setTextureRect(sf::IntRect({frame * frameSize.x, 0}, frameSize));
}

float Enemy::getHealth() const {
    return health;
}

float Enemy::getDamage() const {
    return damage;
}

void Enemy::takeDamage(float takeDamage) {
    health -= takeDamage;
}
