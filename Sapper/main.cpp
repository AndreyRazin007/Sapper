#include <SFML/Graphics.hpp>
#include <ctime>

const signed width{ 32 };
signed gridLogical[12][12];
signed gridView[12][12];

signed main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = { 10 };

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(400, 400), "Sapper");

    sf::Texture texture;
    texture.loadFromFile("Images/tiles.jpg");
    sf::Sprite sprite(texture);

    for (signed i{ 1 }; i <= 10; ++i) {
        for (signed j{ 1 }; j <= 10; ++j) {
            gridView[i][j] = { 10 };

            if (rand() % 5 == 0) {
                gridLogical[i][j] = { 9 };
            }
            else {
                gridLogical[i][j] = { 0 };
            }
        }
    }

    for (signed i{ 1 }; i <= 10; ++i) {
        for (signed j{ 1 }; j <= 10; ++j) {
            signed number{ 0 };

            if (gridLogical[i][j] == 9) {
                continue;
            }

            if (gridLogical[i + 1][j] == 9) {
                ++number;
            }

            if (gridLogical[i][j + 1] == 9) {
                ++number;
            }

            if (gridLogical[i - 1][j] == 9) {
                ++number;
            }

            if (gridLogical[i][j - 1] == 9) {
                ++number;
            }

            if (gridLogical[i + 1][j + 1] == 9) {
                ++number;
            }

            if (gridLogical[i - 1][j - 1] == 9) {
                ++number;
            }

            if (gridLogical[i - 1][j + 1] == 9) {
                ++number;
            }

            if (gridLogical[i + 1][j - 1] == 9) {
                ++number;
            }

            gridLogical[i][j] = { number };
        }
    }

    while (window.isOpen()) {
        sf::Vector2i position{ sf::Mouse::getPosition(window) };
        signed x{ position.x / width };
        signed y{ position.y / width };

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.key.code == sf::Mouse::Left) {
                    gridView[x][y] = gridLogical[x][y];
                }

                else if (event.key.code == sf::Mouse::Right) {
                    gridView[x][y] = { 11 };
                }
            }
        }

        window.clear(sf::Color::White);

        for (signed i{ 1 }; i <= 10; ++i) {
            for (signed j{ 1 }; j <= 10; ++j) {
                if (gridView[x][y] == 9) {
                    gridView[i][j] = { gridLogical[i][j] };
                }

                sprite.setTextureRect(sf::IntRect(gridView[i][j] * width, 0, width, width));
                sprite.setPosition(i * width, j * width);
                window.draw(sprite);
            }
        }

        window.display();
    }

    return 0;
}