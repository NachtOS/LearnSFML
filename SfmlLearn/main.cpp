#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

constexpr float zoneRadius = 70.f;
constexpr float reachZone = 70.f;
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

    sf::Texture enemyIdleTexture;
    if (!enemyIdleTexture.loadFromFile("assets/enemy/Skeleton_01_White_Idle.png")) {
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

    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("assets/HUD/button.png")) {
        return -1;
    }

    sf::Vector2u sheetSize = hpBarTexture.getSize();
    int frameW = static_cast<int>(sheetSize.x) / 9;
    int frameH = static_cast<int>(sheetSize.y);

    sf::Sprite hpBar(hpBarTexture);
    hpBar.setTextureRect(sf::IntRect({0, 0}, {frameW, frameH}));
    hpBar.setScale({3.f, 3.f});
    hpBar.setPosition({5.f, 5.f});

    sf::Sprite buttonResume(buttonTexture);
    buttonResume.setScale({1.5f, 1.5f});
    buttonResume.setPosition({30.f, 220.f});

    sf::Sprite buttonRestart(buttonTexture);
    buttonRestart.setScale({1.5f, 1.5f});
    buttonRestart.setPosition({30.f, 340.f});

    sf::Sprite buttonExitToMainMenu(buttonTexture);
    buttonExitToMainMenu.setScale({1.5f, 1.5f});
    buttonExitToMainMenu.setPosition({30.f, 460.f});

    sf::Sprite buttonPlay(buttonTexture);
    buttonPlay.setScale({1.5f, 1.5f});
    buttonPlay.setPosition({30.f, 220.f});

    sf::Sprite buttonExitTheGame(buttonTexture);
    buttonExitTheGame.setScale({1.5f, 1.5f});
    buttonExitTheGame.setPosition({30.f, 340.f});

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
        enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, enemyIdleTexture, {distX(rng), distY(rng)},
            distSpeed(rng), 160.f, 50.f, 10.f));
    }

    sf::Font font;
    if (!font.openFromFile("assets/font/BoldPixels.ttf")) {
        return -1;
    }

    int kills = 0;
    int score = 0;

    sf::Sprite skullKills(skullKillTexture);
    skullKills.setScale({1.8f, 1.8f});
    skullKills.setPosition({10.f, 100.f});

    sf::Text scoreText(font, "Score: " + std::to_string(score), 20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(1.f);
    scoreText.setPosition({10.f, 140.f});

    sf::Text killsText(font, std::to_string(kills), 20);
    killsText.setFillColor(sf::Color::White);
    killsText.setOutlineColor(sf::Color::Black);
    killsText.setOutlineThickness(1.f);
    killsText.setPosition({50.f, 100.f});

    sf::Text gameOverText(font, "Game Over", 50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(1.f);
    gameOverText.setPosition({40.f, 260.f});

    sf::Text menuPauseText(font, "Pause", 75);
    menuPauseText.setFillColor(sf::Color::Red);
    menuPauseText.setOutlineColor(sf::Color::Black);
    menuPauseText.setOutlineThickness(1.f);
    menuPauseText.setPosition({40.f, 120.f});

    sf::Text huntText(font, "HUNT", 150);
    huntText.setFillColor(sf::Color(143, 13, 22));
    huntText.setOutlineColor(sf::Color::Black);
    huntText.setOutlineThickness(2.f);
    huntText.setPosition({40.f, 30.f});

    sf::Text playText(font, "Play", 32);
    playText.setFillColor(sf::Color::White);
    playText.setOutlineColor(sf::Color::Black);
    playText.setOutlineThickness(1.f);
    playText.setPosition({120.f, 240.f});

    sf::Text exitText(font, "Exit", 32);
    exitText.setFillColor(sf::Color::White);
    exitText.setOutlineColor(sf::Color::Black);
    exitText.setOutlineThickness(1.f);
    exitText.setPosition({120.f, 360.f});

    sf::Text resumeText(font, "Resume", 32);
    resumeText.setFillColor(sf::Color::White);
    resumeText.setOutlineColor(sf::Color::Black);
    resumeText.setOutlineThickness(1.f);
    resumeText.setPosition({105.f, 240.f});

    sf::Text restartText(font, "Restart", 32);
    restartText.setFillColor(sf::Color::White);
    restartText.setOutlineColor(sf::Color::Black);
    restartText.setOutlineThickness(1.f);
    restartText.setPosition({100.f, 360.f});

    sf::Text mainMenuText(font, "Main Menu", 32);
    mainMenuText.setFillColor(sf::Color::White);
    mainMenuText.setOutlineColor(sf::Color::Black);
    mainMenuText.setOutlineThickness(1.f);
    mainMenuText.setPosition({90.f, 480.f});

    sf::View view({static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f}, {bounds.x, bounds.y});

    bool gameOver = false;
    bool inMainMenu = true;
    bool inPauseMenu = false;

    while (window.isOpen()) {
        /* скорость умножается на dt чтобы когда у пользователя фпс высокий то он не был быстрее чем задумано
           или когда фпс низкий то не был медленным */
        const float dt = clock.restart().asSeconds();

        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape && !inPauseMenu) {
                    inPauseMenu = true;
                }
            }
        }

        if (!gameOver && !inPauseMenu && !inMainMenu) {
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
                if (enemies[i].shouldHit() && player.collidesWith(enemies[i]) < reachZone && !player.isDeath()) {
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
                enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, enemyIdleTexture, {distX(rng), distY(rng)},
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
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosition = window.mapPixelToCoords(mousePos);

            if (buttonRestart.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    gameOver = false;
                    score = 0;
                    kills = 0;

                    killsText.setString(std::to_string(kills));
                    scoreText.setString("Score: " + std::to_string(score));

                    player = Player(playerIdleTexture, playerRunTexture, playerAttackTexture, playerDeathTexture,
                        {worldSize.x / 2, worldSize.y / 2}, 300.f, 220.f, 80.f,15.f);
                    coins.clear();
                    enemies.clear();

                    for (int i = 0; i < 3; i++) {
                        enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, enemyIdleTexture, {distX(rng), distY(rng)},
                            distSpeed(rng), 160.f, 50.f, 10.f));
                    }

                    for (int i = 0; i < 10; i++) {
                        coins.push_back(Coin(coinTexture, {distX(rng), distY(rng)}));
                    }
                }
            }

            if (buttonExitToMainMenu.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    gameOver = false;
                    inMainMenu = true;
                }
            }

            window.clear(sf::Color(138, 106, 106));
            window.draw(buttonRestart);
            window.draw(buttonExitToMainMenu);
            window.draw(gameOverText);
            window.draw(restartText);
            window.draw(mainMenuText);
        }

        if (!gameOver && inPauseMenu && !inMainMenu) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosition = window.mapPixelToCoords(mousePos);

            if (buttonResume.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    inPauseMenu = false;
                }
            }

            if (buttonRestart.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    inPauseMenu = false;
                    score = 0;
                    kills = 0;

                    killsText.setString(std::to_string(kills));
                    scoreText.setString("Score: " + std::to_string(score));

                    player = Player(playerIdleTexture, playerRunTexture, playerAttackTexture, playerDeathTexture,
                        {worldSize.x / 2, worldSize.y / 2}, 300.f, 220.f, 80.f,15.f);
                    coins.clear();
                    enemies.clear();

                    for (int i = 0; i < 3; i++) {
                        enemies.push_back(Enemy(enemyWalkTexture, enemyAttackTexture, enemyIdleTexture, {distX(rng), distY(rng)},
                            distSpeed(rng), 160.f, 50.f, 10.f));
                    }

                    for (int i = 0; i < 10; i++) {
                        coins.push_back(Coin(coinTexture, {distX(rng), distY(rng)}));
                    }
                }
            }

            if (buttonExitToMainMenu.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    inPauseMenu = false;
                    inMainMenu = true;
                }
            }

            window.clear(sf::Color(50, 150, 100, 50));
            window.draw(buttonResume);
            window.draw(buttonRestart);
            window.draw(buttonExitToMainMenu);
            window.draw(resumeText);
            window.draw(restartText);
            window.draw(mainMenuText);
            window.draw(menuPauseText);
        } else if (!gameOver && inMainMenu && !inPauseMenu) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosition = window.mapPixelToCoords(mousePos);

            if (buttonPlay.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    inMainMenu = false;
                }
            }

            if (buttonExitTheGame.getGlobalBounds().contains(mousePosition)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    window.close();
                }
            }

            window.clear(sf::Color(56, 56, 56));
            window.draw(buttonPlay);
            window.draw(buttonExitTheGame);
            window.draw(playText);
            window.draw(exitText);
            window.draw(huntText);
        }

        window.display();
     }

    return 0;
}