#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const float PARTICLE_COUNT = 4000;
const float SCREEN_WIDTH = 1920;
const float SCREEN_HEIGHT = 1080;
const float MAX_PARTICLE_SIZE = 2.8f;

std::vector<float> center = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

struct Particle {
    std::vector<float> home;
    std::vector<float> position = home;
    float size = 0.009f;
    bool remove = false;

    Particle() {
        home = {SCREEN_WIDTH / 2 - SCREEN_WIDTH + rand() % (3840), SCREEN_HEIGHT / 2 - SCREEN_HEIGHT + rand() % 2160};
        position = home;
    }
};

class ParticleSystem {
public:
    std::vector<Particle> particles = {};

    void createParticles() {
        while (particles.size() < PARTICLE_COUNT) {
            particles.push_back(createParticle());
        }
    }

    float normalizeVelocity(float originalVelocity) {
        return std::pow(originalVelocity, 0.1f);
    }

    void updateParticles(float amplitude) {

        for (auto& particle : particles) {
            if (amplitude > 1000) {
                particle.position[0] += (particle.position[0] - center[0]) * 0.003f;
                particle.position[1] += (particle.position[1] - center[1]) * 0.003f;
            } else {
                particle.position[0] += (particle.position[0] - center[0]) * 0.0005f;
                particle.position[1] += (particle.position[1] - center[1]) * 0.0005f;
            }

            if (particle.position[0] > SCREEN_WIDTH * 2 || particle.position[1] > SCREEN_HEIGHT * 2 ||
                particle.position[0] < 0 || particle.position[1] < 0) {
                particle.remove = true;
            }


            if (particle.size < MAX_PARTICLE_SIZE) {
                particle.size += 0.0014;
            }
        }
        remove();
        createParticles();
        std::cout << "particles: " << particles.size() << std::endl;
    }

    void remove() {
        particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& particle) {
            return particle.remove;
        }), particles.end());
    }

    void renderParticles(sf::RenderWindow& window) {
        for (const auto& particle : particles) {
            sf::CircleShape shape(particle.size);
            shape.setPosition(particle.position[0], particle.position[1]);
            shape.setFillColor(sf::Color::White);
            window.draw(shape);
        }
    }

    Particle createParticle() {
        Particle particle;
        return particle;
    }
};
