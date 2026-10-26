#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

constexpr float zoneRadius = 70.f;
constexpr int divisions = 8;
constexpr int hpPerDivision = 10;

int main() {
    sf::Vector2u windowSize = {1000, 800};
    const sf::Vector2f bounds(windowSize);
    sf::Vector2f worldSize = {4800.f, 3600.f};

    sf::RenderWindow window(sf::VideoMode(windowSize), "HUNT");
    window.setFramerateLimit(120);

    sf::Texture playerIdleTexture;
    if (!playerIdleTexture.loadFromFile("assets/player/_Idle.png")) {
        return -1;
    }

    sf::Texture playerRunTexture;
    if (!playerRunTexture.loadFromFile("assets/player/_Run.png")) {
        return -1;
    }

    sf::Texture playerAttackTexture;
    if (!playerAttackTexture.loadFromFile("assets/player/_Attack2.png")) {
        return -1;
    }

    sf::Texture playerDeathTexture;
    if (!playerDeathTexture.loadFromFile("assets/player/_Death.png")) {
        return -1;
    }

    sf::Texture enemyWalkTexture;
    if (!enemyWalkTexture.loadFromFile("assets/enemy/Skeleton_01_White_Walk.png")) {
        return -1;
    }

    sf::Texture enemyAttackTexture;
    if (!enemyAttackTexture.loadFromFile("assets/enemy/Skeleton_01_White_Attack1.png")) {
        return -1;
    }

    sf::Texture skullKillTexture;
    if (!skullKillTexture.loadFromFile("assets/Skull.png")) {
        return -1;
    }

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("assets/coin.png")) {
        return -1;
    }

    sf::Texture hpBarTexture;
    if (!hpBarTexture.loadFromFile("assets/HUD/hp_bar.png")) {
        return -1;
    }

    sf::Vector2u sheetSize = hpBarTexture.getSize();
    int frameW = static_cast<int>(sheetSize.x) / 9;
    int frameH = static_cast<int>(sheetSize.y);

    sf::Sprite hpBar(hpBarTexture);
    hpBar.setTextureRect(sf::IntRect({0, 0}, {frameW, frameH}));
    hpBar.setScale({3.f, 3.f});
    hpBar.setPosition({5.f, 5.f});

    Player player(playerIdleTexture, playerRunTexture, playerAttackTexture, playerDeathTexture,
        {worldSize.x / 2, worldSize.y / 2}, 300.f, 220.f, 80.f, 15.f);
    sf::Clock clock;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(15.f, worldSize.x - 15.f);
    std::uniform_real_distribution<float> distY(15.f, worldSize.y - 15.f);

    std::vector<Coin> coins;
    for (int i = 0; i < 10; i++) {
        coins.push_back(Coin(coinTexture, {distX(rng), distY(rng)}));
    }

    std::uniform_real_distribution<float> distSpeed(60.f, 120.f);

    std::vector<Enemy> enemies;
    for (int i = 0; i < 3; i++) {
        enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, {distX(rng), distY(rng)}, distSpeed(rng),
            160.f, 50.f, 10.f));
    }
    // font объявлен раньше текстов, потому что sf::Text хранит ссылку на него
    sf::Font font;
    if (!font.openFromFile("assets/font/BoldPixels.ttf")) {
        return -1;
    }

    int kills = 0;
    int score = 0;
    bool gameOver = false;

    sf::Text scoreText(font, "Score: " + std::to_string(score), 20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 140.f});

    sf::Sprite skullKills(skullKillTexture);
    skullKills.setScale({1.8f, 1.8f});
    skullKills.setPosition({10.f, 100.f});

    sf::Text killsText(font, std::to_string(kills), 20);
    killsText.setFillColor(sf::Color::White);
    killsText.setPosition({50.f, 100.f});

    sf::Text gameOverText(font, "Game Over", 26);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({340.f, 270.f});

    sf::Text pressRText(font, "Press R to restart", 18);
    pressRText.setFillColor(sf::Color::Red);
    pressRText.setPosition({337.f, 300.f});

    sf::View view({static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f}, {bounds.x, bounds.y});

    while (window.isOpen()) {
        /* скорость умножается на dt чтобы когда у пользователя фпс высокий то он не был быстрее чем задумано
           или когда фпс низкий то не был медленным */
        const float dt = clock.restart().asSeconds();

        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
                if (key->code == sf::Keyboard::Key::R && gameOver) {
                    score = 0;
                    kills = 0;
                    gameOver = false;

                    killsText.setString(std::to_string(kills));
                    scoreText.setString("Score: " + std::to_string(score));

                    player = Player(playerIdleTexture, playerRunTexture, playerAttackTexture, playerDeathTexture,
                        {worldSize.x / 2, worldSize.y / 2}, 300.f, 220.f, 80.f,15.f);
                    coins.clear();
                    enemies.clear();

                    for (int i = 0; i < 3; i++) {
                        enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, {distX(rng), distY(rng)},
                            distSpeed(rng), 160.f, 50.f, 10.f));
                    }

                    for (int i = 0; i < 10; i++) {
                        coins.push_back(Coin(coinTexture, {distX(rng), distY(rng)}));
                    }
                }
            }
        }

        if (!gameOver) {
            player.update(dt, worldSize, window);

            if (player.isDeath() && player.isDeathFinished()) {
                gameOver = true;
            }

            if (player.shouldHit()) {
                for (int i = enemies.size() - 1; i >= 0; --i) {
                    sf::Vector2f toEnemy = enemies[i].getPosition() - player.attackZone();
                    if (toEnemy.length() < zoneRadius + enemies[i].getRadius()) {
                        enemies[i].takeDamage(player.getDamage());
                        if (enemies[i].getHealth() <= 0.f) {
                            enemies.erase(enemies.begin() + i);
                            kills++;
                            killsText.setString(std::to_string(kills));
                        }
                    }
                }
            }

            for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i) {
                if (player.collidesWith(enemies[i]) && !player.isDeath()) {
                    player.takeDamage(enemies[i].getDamage());
                }
            }

            for (int i = static_cast<int>(coins.size()) - 1; i >= 0; --i) {
                if (player.collidesWith(coins[i])) {
                    coins.erase(coins.begin() + i);
                    ++score;
                    scoreText.setString("Score: " + std::to_string(score));
                }
            }

            if (coins.empty()) {
                for (int i = 0; i < 10; i++) {
                    float x = distX(rng);
                    float y = distY(rng);

                    coins.push_back(Coin(coinTexture, {x, y}));
                }
            }

            if (enemies.size() < 3) {
                enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, {distX(rng), distY(rng)},
                    distSpeed(rng), 160.f, 50.f, 10.f));
            }

            for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i) {
                enemies[i].chase(player.getPosition(), dt);
            }
        }

        int frameNumber = (static_cast<int>(player.getHealth()) + hpPerDivision - 1) / hpPerDivision;
        if (frameNumber < 0) {
            frameNumber = 0;
        }
        if (frameNumber > divisions) {
            frameNumber = divisions;
        }
        int frameIndex = divisions - frameNumber;
        hpBar.setTextureRect(sf::IntRect({frameIndex * frameW, 0}, {frameW, frameH}));

        sf::Vector2f camPos = player.getPosition();

        if (camPos.x < bounds.x / 2.f) {
            camPos.x = bounds.x / 2.f;
        }
        if (camPos.x > worldSize.x - bounds.x / 2.f) {
            camPos.x = worldSize.x - bounds.x / 2.f;
        }
        if (camPos.y < bounds.y / 2.f) {
            camPos.y = bounds.y / 2.f;
        }
        if (camPos.y > worldSize.y - bounds.y / 2.f) {
            camPos.y = worldSize.y - bounds.y / 2.f;
        }

        view.setCenter(camPos);
        window.setView(view);
        window.clear(sf::Color(0, 0, 200));

        for (int i = 0; i <= static_cast<int>(worldSize.x); i += 100) {
            sf::RectangleShape lineX({2.f, worldSize.y});
            lineX.setPosition({static_cast<float>(i), 0.f});
            lineX.setFillColor(sf::Color(35, 35, 220));
            window.draw(lineX);
        }

        for (int i = 0; i <= static_cast<int>(worldSize.y); i += 100) {
            sf::RectangleShape lineX({worldSize.x, 2.f});
            lineX.setPosition({0.f,  static_cast<float>(i)});
            lineX.setFillColor(sf::Color(35, 35, 220));
            window.draw(lineX);
        }

        for (const Coin& coin : coins) {
            coin.draw(window);
        }

        for (const Enemy& enemy : enemies) {
            enemy.draw(window);
        }

        player.draw(window);
        window.setView(window.getDefaultView());
        window.draw(hpBar);
        window.draw(scoreText);
        window.draw(skullKills);
        window.draw(killsText);

        if (gameOver) {
            window.draw(gameOverText);
            window.draw(pressRText);
        }

        window.display();
     }

    return 0;
}