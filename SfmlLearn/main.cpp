#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

int main() {
    sf::Vector2u windowSize = {800, 600};
    const sf::Vector2f bounds(windowSize);
    sf::Vector2f worldSize = {2400.f, 1800.f};

    sf::RenderWindow window(sf::VideoMode(windowSize), "MyGameSFML");
    window.setFramerateLimit(120);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player.png")) {
        return -1;
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("assets/enemy.png")) {
        return -1;
    }

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("assets/coin.png")) {
        return -1;
    }

    Player player(50.f, {worldSize.x / 2, worldSize.y / 2}, 300);
    player.setTexture(playerTexture);
    sf::Clock clock;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(15.f, worldSize.x - 15);
    std::uniform_real_distribution<float> distY(15.f, worldSize.y - 15);

    std::vector<Coin> coins;
    for (int i = 0; i < 10; i++) {
        coins.push_back(Coin(15.f, {distX(rng), distY(rng)}, coinTexture));
    }

    std::uniform_real_distribution<float> distSpeed(60.f, 120.f);

    std::vector<Enemy> enemies;
    for (int i = 0; i < 3; i++) {
        enemies.push_back(Enemy({distX(rng), distY(rng)},
            distSpeed(rng), 25.f, enemyTexture));
    }
    // font объявлен раньше текстов, потому что sf::Text хранит ссылку на него
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        return -1;
    }

    int lives = 3;
    int score = 0;
    bool gameOver = false;

    sf::Text scoreText(font, "Score: " + std::to_string(score), 16);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});

    sf::Text livesText(font, "Lives: " + std::to_string(lives), 16);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition({10.f, 25.f});

    sf::Text gameOverText(font, "Game Over", 26);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({340.f, 270.f});

    sf::Text pressRText(font, "Press R to restart", 18);
    pressRText.setFillColor(sf::Color::Red);
    pressRText.setPosition({337.f, 300.f});

    sf::View view({400.f, 300.f}, {800.f, 600.f});

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
                    lives = 3;
                    gameOver = false;

                    livesText.setString("Lives: " + std::to_string(lives));
                    scoreText.setString("Score: " + std::to_string(score));

                    player = Player(50.f, {windowSize.x / 2.f, windowSize.y / 2.f}, 300);
                    player.setTexture(playerTexture);
                    coins.clear();
                    enemies.clear();

                    for (int i = 0; i < 3; i++) {
                        enemies.push_back(Enemy({distX(rng), distY(rng)},
                            distSpeed(rng), 25.f, enemyTexture));
                    }

                    for (int i = 0; i < 10; i++) {
                        coins.push_back(Coin(15.f, {distX(rng), distY(rng)}, coinTexture));
                    }
                }
            }
        }

        if (!gameOver) {
            player.update(dt, worldSize);

            for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i) {
                if (player.collidesWith(enemies[i])) {
                    enemies.erase(enemies.begin() + i);
                    --lives;
                    livesText.setString("Lives: " + std::to_string(lives));
                    if (lives == 0) gameOver = true;
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

                    coins.push_back(Coin(15.f, {x, y}, coinTexture));
                }
            }

            if (enemies.size() < 3) {
                enemies.push_back(Enemy({distX(rng), distY(rng)},
                                distSpeed(rng), 25.f, enemyTexture));
            }

            for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i) {
                enemies[i].chase(player.getPosition(), dt);
            }
        }

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

        for (float i = 0; i <= worldSize.x; i += 100) {
            sf::RectangleShape lineX({2.f, worldSize.y});
            lineX.setPosition({i, 0.f});
            lineX.setFillColor(sf::Color(35, 35, 220));
            window.draw(lineX);
        }

        for (float i = 0; i <= worldSize.y; i += 100) {
            sf::RectangleShape lineX({worldSize.x, 2.f});
            lineX.setPosition({0.f, i});
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
        window.draw(scoreText);
        window.draw(livesText);

        if (gameOver) {
            window.draw(gameOverText);
            window.draw(pressRText);
        }

        window.display();
     }

    return 0;
}