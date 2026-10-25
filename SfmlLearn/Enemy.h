#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(const sf::Texture& runTex, sf::Vector2f pos, float speed, float size, float heath);
    void chase(sf::Vector2f target, float dt);
    float getHealth() const;
    void takeDamage(float damage);
private:
    const sf::Texture* runTexture;
    sf::Vector2i frameSize;
    int runFrames;
    int frameCount;
    float frameTime;
    int frame = 0;
    float frameTimer = 0.f;
    float speed;
    float health;
};
