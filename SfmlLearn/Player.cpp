#include <cmath>

#include "Player.h"

Player::Player(const sf::Texture& idleTex, const sf::Texture& runTex, const sf::Texture& attackTex, const sf::Texture& deathTex,
    sf::Vector2f pos, float speed, float size, float maxHealth, float damage)
    : Entity(idleTex, pos, size, 36.f), idleTexture(&idleTex), runTexture(&runTex), attackTexture(&attackTex),
    deathTexture(&deathTex), idleFrames(10), runFrames(10), attackFrames(6), deathFrames(10), speed(speed), health(maxHealth),
    maxHealth(maxHealth), damage(damage), frameSize(120, 80), frameCount(idleFrames), frameTime(0.08f) {
    setFrame(sf::IntRect({0, 0}, frameSize), size);
}

void Player::update(float dt, sf::Vector2f bounds, sf::RenderWindow& window) {
    PlayerState newState = PlayerState::Idle;

    if (isDeath()) {
        newState = PlayerState::Death;
        animate(dt, newState);
        return;
    }

    if (!attacking) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sprite.move({-speed * dt, 0.f});
            newState = PlayerState::Run;
            sprite.setScale({-std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            sprite.move({speed * dt, 0.f});
            newState = PlayerState::Run;
            sprite.setScale({std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            sprite.move({0.f, -speed * dt});
            newState = PlayerState::Run;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            sprite.move({0.f, speed * dt});
            newState = PlayerState::Run;
        }
    }

    bool mouseIsDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    sf::Vector2i mousePosition(sf::Mouse::getPosition(window));
    if (mousePosition.x <= bounds.x && mousePosition.x >= 0.f && mousePosition.y <= bounds.y && mousePosition.y >= 0.f) {
        if (mouseIsDown) {
            if (!mouseWasDown && !attacking) {
                attacking = true;
                damageDealt = false;
            }
        }

        if (attacking) {
            newState = PlayerState::Attack;
        }
    }

    sf::Vector2f pos = sprite.getPosition();

    if (pos.x < radius) pos.x = radius;
    if (pos.x > bounds.x - radius) pos.x = bounds.x - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > bounds.y - radius) pos.y = bounds.y - radius;

    mouseWasDown = mouseIsDown;
    sprite.setPosition(pos);
    animate(dt, newState);
}

void Player::animate(float dt, PlayerState newState) {
    if (state != newState) {
        state = newState;
        frame = 0;
        frameTimer = 0;

        switch (state) {
            case PlayerState::Idle:
                sprite.setTexture(*idleTexture);
                frameCount = idleFrames;
                break;
            case PlayerState::Run:
                sprite.setTexture(*runTexture);
                frameCount = runFrames;
                break;
            case PlayerState::Attack:
                sprite.setTexture(*attackTexture);
                frameCount = attackFrames;
                break;
            case PlayerState::Death:
                sprite.setTexture(*deathTexture);
                frameCount = deathFrames;
                break;
            default:
                sprite.setTexture(*idleTexture);
                frameCount = idleFrames;
                break;
        }
    }

    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        if (!(state == PlayerState::Death && frame == frameCount - 1)) {
            frame = (frame + 1) % frameCount;
        }
        if (frame == 0 && attacking) {
            attacking = false;
        }
    }

    sprite.setTextureRect(sf::IntRect({frame * frameSize.x, 0}, frameSize));
}

bool Player::shouldHit() {
    if (state == PlayerState::Attack && !damageDealt) {
        if (frame == hitFrame) {
            damageDealt = true;
            return damageDealt;
        }
    }
    return false;
}

sf::Vector2f Player::attackZone() const {
    sf::Vector2f playerPos(sprite.getPosition());
    float offset = 60.f;
    if (sprite.getScale().x < 0.f) {
        offset = -60.f;
    }

    return {playerPos.x + offset, playerPos.y};
}

float Player::getDamage() const {
    return damage;
}

float Player::getHealth() const {
    return health;
}

void Player::takeDamage(float takeDamage) {
    health -= takeDamage;
}

bool Player::isDeath() const {
    if (health <= 0) {
        return true;
    }
    return false;
}

bool Player::isDeathFinished() const {
    if (state == PlayerState::Death && frame == frameCount - 1) {
        return true;
    }
    return false;
}
