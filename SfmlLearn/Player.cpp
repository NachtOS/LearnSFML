#include "Player.h"

Player::Player(float radius, sf::Vector2f startPos, float speed)
    : shape(radius), radius(radius), speed(speed) {
    shape.setFillColor(sf::Color(0, 200, 10));
    shape.setOrigin({radius, radius});
    shape.setPosition(startPos);
}

void Player::update(float dt, sf::Vector2f bounds) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape.move({-speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape.move({speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        shape.move({0.f, -speed * dt});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        shape.move({0.f, speed * dt});
    }

    sf::Vector2f pos = shape.getPosition();

    if (pos.x < radius) pos.x = radius;
    if (pos.x > bounds.x - radius) pos.x = bounds.x - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > bounds.y - radius) pos.y = bounds.y - radius;

    shape.setPosition(pos);
}

void Player::draw(sf::RenderWindow &window) const {
    window.draw(shape);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

float Player::getRadius() const {
    return radius;
}
