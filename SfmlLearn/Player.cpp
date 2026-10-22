#include "Player.h"

Player::Player(const sf::Texture& texture, sf::Vector2f pos, float speed)
    : Entity(texture, pos, 120.f, 28.f), speed(speed), frameSize(120, 80), frameCount(10), frameTime(0.1f) {
    setFrame(sf::IntRect({0, 0}, frameSize), 120.f);
}

void Player::update(float dt, sf::Vector2f bounds) {
    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        sprite.move({-speed * dt, 0.f});
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        sprite.move({speed * dt, 0.f});
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        sprite.move({0.f, -speed * dt});
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
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
    if (!moving) {
        frame = 0;
        frameTimer = 0;
    } else {
        frameTimer += dt;
        if (frameTimer >= frameTime) {
            frameTimer -= frameTime;
            frame = (frame + 1) % frameCount;
        }
    }
}
