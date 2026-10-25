#pragma once

#include "Entity.h"

enum class State { Idle, Run, Attack };

class Player : public Entity {
public:
    Player(const sf::Texture& idleTex, const sf::Texture& runTex, const sf::Texture& attackTex, sf::Vector2f startPos,
        float speed, float size, float damage);
    void update(float dt, sf::Vector2f bounds, sf::RenderWindow& window) override;
    bool shouldHit();
    sf::Vector2f attackZone() const;
    float getDamage() const;

private:
    const sf::Texture* idleTexture;
    const sf::Texture* runTexture;
    const sf::Texture* attackTexture;
    int idleFrames;
    int runFrames;
    int attackFrames;
    State state = State::Idle;
    float speed;
    float damage;
    sf::Vector2i frameSize;
    int frameCount;
    float frameTime;
    int frame = 0;
    int hitFrame = 3;
    float frameTimer = 0.f;
    bool mouseWasDown = false;
    bool attacking = false;
    bool damageDealt = false;

    void animate(float dt, State state);
};
