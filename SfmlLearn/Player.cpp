#include "Player.h"

Player::Player(float radius, sf::Vector2f startPos, float speed)
    : Entity(radius, sf::Color(0, 200, 10), startPos), speed(speed) {}

void Player::update(float dt, sf::Vector2f bounds) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        entity.move({-speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        entity.move({speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        entity.move({0.f, -speed * dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        entity.move({0.f, speed * dt});
    }

    sf::Vector2f pos = entity.getPosition();

    if (pos.x < radius) pos.x = radius;
    if (pos.x > bounds.x - radius) pos.x = bounds.x - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > bounds.y - radius) pos.y = bounds.y - radius;

    entity.setPosition(pos);
}