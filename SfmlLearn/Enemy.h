#pragma once

#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(const sf::Texture& runTex, sf::Vector2f pos, float speed, float size);
    void chase(sf::Vector2f target, float dt);
private:
    const sf::Texture* runTexture;
    sf::Vector2i frameSize;
    int runFrames;
    int frameCount;
    float frameTime;
    int frame = 0;
    float frameTimer = 0.f;
    float speed;
};
