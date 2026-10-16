#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Player.h"
#include "Coin.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "MyGameSFML");
    window.setFramerateLimit(120);

    Player player(50.f, {400.f, 300.f}, 300);
    sf::Clock clock;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(15.f, 785.f);
    std::uniform_real_distribution<float> distY(15.f, 585.f);

    std::vector<Coin> coins;
    for (int i = 0; i < 10; i++) {
        float x = distX(rng);
        float y = distY(rng);

        coins.push_back(Coin({x, y}, 15.f));
    }

    int score = 0;

    while (window.isOpen()) {
        /* скорость умножается на dt чтобы когда у пользователя фпс высокий то он не был быстрее чем задумано
           или когда фпс низкий то не был медленным */
        float dt = clock.restart().asSeconds();

        while (std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        player.update(dt, {800.f, 600.f});

        for (int i = static_cast<int>(coins.size()) - 1; i >= 0; --i) {
            float dx = player.getPosition().x - coins[i].getPosition().x;
            float dy = player.getPosition().y - coins[i].getPosition().y;
            float r = player.getRadius() + coins[i].getRadius();

            if (dx * dx + dy * dy < r * r) {
                coins.erase(coins.begin() + i);
                ++score;
                window.setTitle("Score: " + std::to_string(score));
            }
        }

        if (coins.empty()) {
            for (int i = 0; i < 10; i++) {
                float x = distX(rng);
                float y = distY(rng);

                coins.push_back(Coin({x, y}, 15.f));
            }
        }

        window.clear(sf::Color(0, 0, 200));
        for (const Coin& coin : coins) {
            coin.draw(window);
        }
        player.draw(window);
        window.display();
    }

    return 0;
}
