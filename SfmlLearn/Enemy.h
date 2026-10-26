#pragma once

#include "Entity.h"

enum class EnemyState { Idle, Walk, Attack, Death };

class Enemy : public Entity {
public:
    Enemy(const sf::Texture& walkTex, const sf::Texture& attackTex, const sf::Texture& idleTex, sf::Vector2f pos, float speed, float size, float health, float damage);
    void chase(sf::Vector2f target, float dt);
    float getHealth() const;
    float getDamage() const;
    void takeDamage(float damage);

private:
    const sf::Texture* walkTexture;
    const sf::Texture* attackTexture;
    const sf::Texture* idleTexture;
    int walkFrames;
    int attackFrames;
    int idleFrames;
    EnemyState state = EnemyState::Idle;
    sf::Vector2i frameSize;
    int frameCount;
    float frameTime;
    int frame = 0;
    float frameTimer = 0.f;
    float speed;
    float health;
    float damage;
    float cooldown = 0.f;
    bool attackDone = false;
};
