#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>

#include "particle.h"
using namespace std;

int main() {
    // Particle setup
    double gConst = 6.6743 * pow(10, -11);
    double multiplier = 1000000000 * gConst;
    vector<Particle> particles;
    vector<sf::Text> texts;


    // SFML Setup
    int XRes = 800;
    int YRes = 800;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(XRes, YRes), "Simulation");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    bool clickLock;

    sf::Font font;
    font.loadFromFile("../arial.ttf");

    // Main loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            // Exiting
            if (event.type == sf::Event::Closed)
                window.close();
            // Reset mouse click
            if (event.type == sf::Event::MouseButtonReleased) {
               if (event.mouseButton.button == sf::Mouse::Left) {
                   clickLock = false;
               }
            }
            // On mouse click spawn particle
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !clickLock) {
                    clickLock = true;
                    sf::Vector2 mousePos = sf::Mouse::getPosition(window);
                    /*cout << "Mass? " << endl;
                    double mass;
                    cin >> mass;*/
                    // Set particle id (position in list), state (unused),
                    // and mass/magnitude (used as mass right now for gravity sim)
                    Particle particle((int)particles.size(), 0, 100);
                    particle.Initialize();
                    particle.Set(mousePos.x,mousePos.y);

                    particles.push_back(particle);
                }
            }
        }

        // Calculations
        // Get elapsed time, just as one variable so that they all use the same amount
        double elapsedTime = clock.getElapsedTime().asSeconds();
        for (Particle& particle : particles) {
            // Calculate acceleration
            particle.Calculate(particles, multiplier);
            // Calculate velocity based on acceleration and passed time
            particle.XVel += particle.XAcc * elapsedTime;
            particle.YVel += particle.YAcc * elapsedTime;
            // Move particle based on velocity
            particle.Move(particle.XVel, particle.YVel);
        }

        // Resets and Drawing
        clock.restart();
        window.clear();
        for (const Particle& particle : particles) {
            window.draw(particle.shape);
        }

        window.display();
    }

    return 0;
}