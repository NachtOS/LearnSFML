#pragma once

#include "Entity.h"

enum class State { Idle, Run, Attack, Death };

class Player : public Entity {
public:
    Player(const sf::Texture& idleTex, const sf::Texture& runTex, const sf::Texture& attackTex, const sf::Texture& deathTex,
        sf::Vector2f startPos, float speed, float size, float maxHealth, float damage);
    void update(float dt, sf::Vector2f bounds, sf::RenderWindow& window) override;
    bool shouldHit();
    bool isDead() const;
    sf::Vector2f attackZone() const;
    float getDamage() const;
    float getHealth() const;
    void takeDamage(float takeDamage);

private:
    // Textures
    const sf::Texture* idleTexture;
    const sf::Texture* runTexture;
    const sf::Texture* attackTexture;
    const sf::Texture* deathTexture;
    int idleFrames;
    int runFrames;
    int attackFrames;
    int deathFrames;

    // Player characteristics
    float speed;
    float health;
    float maxHealth;
    float damage;
    float invulnDuration = 1.f;
    float invulnTimer = 0.f;

    // Animation
    State state = State::Idle;
    sf::Vector2i frameSize;
    int frameCount;
    int frame = 0;
    int hitFrame = 3;
    float frameTime;
    float frameTimer = 0.f;

    // Attack management
    bool mouseWasDown = false;
    bool attacking = false;
    bool damageDealt = false;

    void animate(float dt, State state);
};
