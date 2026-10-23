#include <cmath>

#include "Player.h"

Player::Player(const sf::Texture& idleTex, const sf::Texture& runTex, const sf::Texture& attackTex, sf::Vector2f pos,
    float speed, float size)
    : Entity(idleTex, pos, size, 32.f), idleTexture(&idleTex), runTexture(&runTex), attackTexture(&attackTex),
    idleFrames(10), runFrames(10), attackFrames(6), speed(speed), frameSize(120, 80), frameCount(idleFrames), frameTime(0.08f) {
    setFrame(sf::IntRect({0, 0}, frameSize), size);
}

void Player::update(float dt, sf::Vector2f bounds) {
    State newState = State::Idle;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        sprite.move({-speed * dt, 0.f});
        newState = State::Run;
        sprite.setScale({-std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        sprite.move({speed * dt, 0.f});
        newState = State::Run;
        sprite.setScale({std::abs(sprite.getScale().x), std::abs(sprite.getScale().y)});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        sprite.move({0.f, -speed * dt});
        newState = State::Run;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        sprite.move({0.f, speed * dt});
        newState = State::Run;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        newState = State::Attack;
    }

    sf::Vector2f pos = sprite.getPosition();

    if (pos.x < radius) pos.x = radius;
    if (pos.x > bounds.x - radius) pos.x = bounds.x - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > bounds.y - radius) pos.y = bounds.y - radius;

    sprite.setPosition(pos);
    animate(dt, newState);
}

void Player::animate(float dt, State newState) {
    state = newState;
    switch (state) {
        case State::Idle:
            sprite.setTexture(*idleTexture);
            frameCount = idleFrames;
            break;
        case State::Run:
            sprite.setTexture(*runTexture);
            frameCount = runFrames;
            break;
        case State::Attack:
            sprite.setTexture(*attackTexture);
            frameCount = attackFrames;
            break;
        default:
            sprite.setTexture(*idleTexture);
            frameCount = idleFrames;
            break;
    }

    frameTimer += dt;
    if (frameTimer >= frameTime) {
        frameTimer -= frameTime;
        frame = (frame + 1) % frameCount;
    }

    sprite.setTextureRect(sf::IntRect({frame * frameSize.x, 0}, frameSize));
}
