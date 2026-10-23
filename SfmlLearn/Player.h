#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(const sf::Texture& idleTex, const sf::Texture& runTex, sf::Vector2f startPos, float speed, float size);
    void update(float dt, sf::Vector2f bounds) override;

private:
    const sf::Texture* idleTexture;
    const sf::Texture* runTexture;
    int idleFrames;
    int runFrames;
    bool wasMoving = false;
    float speed;
    sf::Vector2i frameSize;
    int frameCount;
    float frameTime;
    int frame = 0;
    float frameTimer = 0.f;

    void animate(float dt, bool moving);
};
