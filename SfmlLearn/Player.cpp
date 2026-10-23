#include <cmath>

#include "Player.h"

Player::Player(const sf::Texture& idleTex, const sf::Texture& runTex, sf::Vector2f pos, float speed, float size)
    : Entity(idleTex, pos, size, 32.f), idleTexture(&idleTex), runTexture(&runTex), idleFrames(10), runFrames(10),
    speed(speed), frameSize(120, 80), frameCount(idleFrames), frameTime(0.08f) {
    setFrame(sf::IntRect({0, 0}, frameSize), size);
}

void Player::update(float dt, sf::Vector2f bounds) {
    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        sprite.move({-speed * dt, 0.f});
        moving = true;
        sprite.setScale({-std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        sprite.move({speed * dt, 0.f});
        moving = true;
        sprite.setScale({std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        sprite.move({0.f, -speed * dt});
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        sprite.move({0.f, speed * dt});
        moving = true;
    }

    sf::Vector2f pos = sprite.getPosition();

    if (pos.x < radius) pos.x = radius;
    if (pos.x > bounds.x - radius) pos.x = bounds.x - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > bounds.y - radius) pos.y = bounds.y - radius;

    sprite.setPosition(pos);
    animate(dt, moving);
}

void Player::animate(float dt, bool moving) {
    if (moving != wasMoving) {
        wasMoving = moving;
        frame = 0;
        frameTimer = 0;
        if (moving) {
            sprite.setTexture(*runTexture);
            frameCount = runFrames;
        } else {
            sprite.setTexture(*idleTexture);
            frameCount = idleFrames;
        }
    }

    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        frame = (frame + 1) % frameCount;
    }

    sprite.setTextureRect(sf::IntRect({frame * frameSize.x, 0}, frameSize));
}
