#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "particle.h"
#include "images.hpp"



class AudioVisualizerWindow {
public:
    sf::SoundBuffer buffer;
    sf::Music music;

    ParticleSystem particleSystem;
    Images images;

    std::size_t chunkSize;

    AudioVisualizerWindow(sf::RenderWindow& renderWindow) : window(renderWindow) {
        // Initialize chunkSize after loading buffer
        if (!buffer.loadFromFile("../song/song.wav")) {
            std::cerr << "Error loading song buffer\n";
            std::exit(-1);
        }
        chunkSize = buffer.getSampleRate() / 10;

        if (!music.openFromFile("../song/song.wav")) {
            std::cerr << "Error opening song for playback\n";
            std::exit(-1);
        }
    }

    void run() {
        music.play();
        while (window.isOpen()) {
            handleEvents();
            render();
        }
    }

private:
    sf::RenderWindow& window;

    float computeAmplitudeInRange(const sf::Int16* samples, std::size_t count, float lowFreq, float highFreq) {
        // Assuming lowFreq and highFreq are in Hz
        float sampleRate = 44100.0f;  // Adjust this based on your actual sample rate
        float lowBin = lowFreq / (sampleRate / 2) * count;
        float highBin = highFreq / (sampleRate / 2) * count;

        float sum = 0.0f;
        for (std::size_t i = static_cast<std::size_t>(lowBin); i < static_cast<std::size_t>(highBin); ++i) {
            sum += std::abs(samples[i]);
        }
        return sum / (highBin - lowBin);
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    void render() {
        sf::Time offset = music.getPlayingOffset();
        const sf::Int16* samples = buffer.getSamples();
        std::size_t sampleIndex = static_cast<std::size_t>(offset.asSeconds() * buffer.getSampleRate() * buffer.getChannelCount());

        std::size_t chunkSize = buffer.getSampleRate() / 10;

        float lowFrequency = 100.0f;
        float highFrequency = 500.0f;
        float averageAmplitude = computeAmplitudeInRange(samples + sampleIndex, chunkSize, lowFrequency, highFrequency);

        std::cout << "Average Amplitude: " << averageAmplitude << std::endl;

        particleSystem.createParticles();
        particleSystem.updateParticles(averageAmplitude);

        window.clear(sf::Color::Black);

        //window.draw(backgroundImage);

        particleSystem.renderParticles(window);
        
        //window.draw(logoImage);
        window.draw(images.title);
        
        window.display();
    }
};
