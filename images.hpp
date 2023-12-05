#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

    sf::Sprite logoImage;
    sf::Sprite backgroundImage;
    sf::Texture logo;
    sf::Texture backgroundTexture;
    

class Images 
{
    public:
    sf::Text title;
    sf::Font font;
    Images()
    {
    
        if (!backgroundTexture.loadFromFile("../image/img2.jpg")) {
            std::cerr << "Error loading background image\n";
            std::exit(-1);
        }
        backgroundImage.setTexture(backgroundTexture);

        if (!logo.loadFromFile("../image/logo.jpg")) {
            std::cerr << "Error loading logo image\n";
            std::exit(-1);
        }
        logoImage.setTexture(logo);

        std::cout << "Background Texture Size: " << backgroundTexture.getSize().x << "x" << backgroundTexture.getSize().y << std::endl;
        std::cout << "Logo Texture Size: " << logo.getSize().x << "x" << logo.getSize().y << std::endl;

        backgroundImage.setScale(
            1920.f / static_cast<float>(backgroundTexture.getSize().x),
            1080.f / static_cast<float>(backgroundTexture.getSize().y)
        );
        logoImage.setOrigin(logoImage.getLocalBounds().width / 2, logoImage.getLocalBounds().height / 2);
        logoImage.setPosition(sf::Vector2f(1920.f / 2, 1080.f / 2));
        float scaleFactor = 0.5f;
        logoImage.setScale(scaleFactor, scaleFactor);

        if (!font.loadFromFile("../font/font.ttf")) {
            std::cerr << "Error loading font\n";
            std::exit(-1);
        }


        title.setCharacterSize(500);
        title.setFillColor(sf::Color::Red);
        title.setPosition(100, 100);
        title.setStyle(sf::Text::Bold | sf::Text::Underlined);


        title.setString("Title");
    }
};