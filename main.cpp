#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <cmath>
#include "MenuWindow.hpp"




int main() {
    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Audio Visualizer");
    AudioVisualizerWindow audioVisualizerWindow(window); // Pass the window instance to the constructor
    audioVisualizerWindow.run();

    return 0;
}

