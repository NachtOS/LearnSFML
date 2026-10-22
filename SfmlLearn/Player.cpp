#include "Player.h"

Player::Player(const sf::Texture& texture, sf::Vector2f pos, float speed)
    : Entity(texture, pos, 100.f, 28.f), speed(speed) {}

void Player::update(float dt, sf::Vector2f bounds) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        sprite.move({-speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        sprite.move({speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        sprite.move({0.f, -speed * dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        sprite.move({0.f, speed * dt});
    }

    sf::Vector2f pos = sprite.getPosition();

    if (pos.x < radius) pos.x = radius;
    if (pos.x > bounds.x - radius) pos.x = bounds.x - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > bounds.y - radius) pos.y = bounds.y - radius;

    sprite.setPosition(pos);
}