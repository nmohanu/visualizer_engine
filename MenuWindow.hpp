#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <cmath>
#include "AudioVisualizerWindow.hpp"

class MenuWindow {
public:
    MenuWindow() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Menu") {
        if (!playButtonTexture.loadFromFile("../image/logo.jpg")) {
            std::cerr << "Error loading image\n";
            std::exit(-1);
        }

        playButton.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - playButton.getLocalBounds().width / 2,
                                            SCREEN_HEIGHT / 2 - playButton.getLocalBounds().height / 2));
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Texture playButtonTexture;
    sf::Sprite playButton;

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
 
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    window.close();  // Close the menu window
                }
            }
        }
    }

    void update() {
      
    }

    void render() {
        window.clear(sf::Color::Black);
        window.draw(playButton);
        window.display();
    }
};