#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Player.h"
#include "Coin.h"
#include "Enemy.h"
#include "Entity.h"

int main() {
    sf::Vector2u windowSize = {800, 600};
    sf::Vector2f bounds(windowSize);

    sf::RenderWindow window(sf::VideoMode(windowSize), "MyGameSFML");
    window.setFramerateLimit(120);

    Player player(50.f, {400.f, 300.f}, 300);
    sf::Clock clock;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(15.f, 785.f);
    std::uniform_real_distribution<float> distY(15.f, 585.f);

    std::vector<Coin> coins;
    for (int i = 0; i < 10; i++) {
        coins.push_back(Coin(15.f, {distX(rng), distY(rng)}));
    }

    std::uniform_real_distribution<float> distSpeed(-200.f, 200.f);

    std::vector<Enemy> enemies;
    for (int i = 0; i < 3; i++) {
        enemies.push_back(Enemy({distX(rng), distY(rng)},
            {distSpeed(rng), distSpeed(rng)}, 25.f));
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

                    player = Player(50.f, {400.f, 300.f}, 300);
                    coins.clear();
                    enemies.clear();

                    for (int i = 0; i < 3; i++) {
                        enemies.push_back(Enemy({distX(rng), distY(rng)},
                            {distSpeed(rng), distSpeed(rng)}, 25.f));
                    }

                    for (int i = 0; i < 10; i++) {
                        coins.push_back(Coin(15.f, {distX(rng), distY(rng)}));
                    }
                }
            }
        }

        if (!gameOver) {
            player.update(dt, bounds);
            for (int i = static_cast<int>(enemies.size()) - 1; i >= 0; --i) {
                enemies[i].update(dt, bounds);
            }

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

                    coins.push_back(Coin(15.f, {x, y}));
                }
            }

            if (enemies.size() < 3) {
                enemies.push_back(Enemy({distX(rng), distY(rng)},
                                {distSpeed(rng), distSpeed(rng)}, 25.f));
            }
        }

        window.clear(sf::Color(0, 0, 200));

        for (const Coin& coin : coins) {
            coin.draw(window);
        }

        for (const Enemy& enemy : enemies) {
            enemy.draw(window);
        }

        window.draw(scoreText);
        window.draw(livesText);
        player.draw(window);

        if (gameOver) {
            window.draw(gameOverText);
            window.draw(pressRText);
        }

        window.display();
     }

    return 0;
}