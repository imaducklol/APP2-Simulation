#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
using namespace std;

class Particle {
public:
    int id;
    int state;
    double mass;
    double XVel;
    double YVel;
    double XPos;
    double YPos;
    sf::CircleShape shape;

    explicit Particle(int iid = 0, int istate = 0, double imass = 10, double ixvel = 0, double ivel = 0, double ixpos= 0, double iypos = 0) {
        id = iid;
        state = istate;
        mass = imass;
        XVel = ixvel;
        YVel = ivel;
        XPos = ixpos;
        YPos = iypos;
    }
};

void AddParticle (vector<Particle> &particles) {
    Particle particle;
    double input;

    particle.id = (int)particles.size();

    /*cout << "dynamic(0), static(1), or mouse controlled(2)\n";
    cin >> input;
    particle.state = (int)input;*/

    cout << "mass\n";
    cin >> input;
    particle.mass = input;

    /*cout << "vel x\n";
    cin >> input;
    particle.vel = input;

    cout << "vel y\n";
    cin >> input;
    particle.dir = input;*/

    cout << "pos x\n";
    cin >> input;
    particle.XPos = input;

    cout << "pos y\n";
    cin >> input;
    particle.YPos = input;

    particles.push_back(particle);
}

void ListParticles (const vector<Particle>& particles) {
    if (particles.empty()) cout << "None yet" << endl;
    else
    for (Particle particle : particles) {
        cout <<
        "id " << particle.id    << endl <<
        "state " << particle.state << endl <<
        "mass " << particle.mass  << endl << endl;
    }
}

int main() {
    // Particle setup
    double gConst = 6.6743 * pow(10, -11);
    //double rad2dec = 180 / atan(1) * 4;
    uint64_t multiplier = INT64_MAX;
    multiplier = 1000000000000;
    vector<Particle> particles;

    /*while (true) {
        int input;
        cout << "Add Particle (1), list particles (2), run simulation (3)\n";
        cin >> input;

        switch (input) {
            case 1: {
                AddParticle(particles);
                break;
            }
            case 2: {
                ListParticles(particles);
                break;
            }
            case 3: {
                goto programStart;
            }
            default: {
                cout << "That wasn't a listed option now was it\n";
                break;
            }
        }
    }
    programStart:*/
    /*Particle particle1(0, 0, 100, 0, 0, 100, 100);
    Particle particle2(1, 0, 100, 0, 0, 600, 600);
    Particle particle3(3, 0, 100, 0, 0, 100, 600);
    particles.push_back(particle1);
    particles.push_back(particle2);
    particles.push_back(particle3);*/

    // Initialize the actual circle shape for sfml
    for (Particle& particle : particles) {
        double x = particle.mass;
        /*if (x < -100) {
            particle.shape.setRadius(abs(.05 * x - 95));
        } else if (x >= -100 && x <= 100) {
            particle.shape.setRadius(abs(x));
        } else if (x > 100) {
            particle.shape.setRadius(abs(.05 * x + 95));
        }*/
        double radius = abs(x);
        particle.shape.setRadius(radius);

        particle.shape.setPosition(particle.XPos - radius, particle.YPos - radius);
    }

    // SFML Setup
    int XRes = 400;
    int YRes = 400;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;
    sf::RenderWindow window(sf::VideoMode(XRes, YRes), "Simulation");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    /*sf::Font font;
    font.loadFromFile("../arial.ttf");
    sf::Text p1p;
    sf::Text p2p;
    p1p.setFont(font);
    p2p.setFont(font);
    p1p.setCharacterSize(20);
    p2p.setCharacterSize(20);
    //tFPS.setFillColor(Color::White);
    //tFPS.setStyle(Text::Bold);
    p1p.setPosition(200, 30);
    p2p.setPosition(200, 60);*/


    // Main loop
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    double x = sf::Mouse::getPosition(window).x;
                    double y = sf::Mouse::getPosition(window).y;
                    Particle particle(particles.size(), 0, 10, 0, 0, x, y);

                    double radius = abs(particle.mass);
                    particle.shape.setRadius(radius);
                    particle.shape.setFillColor(sf::Color::White);
                    particle.shape.setPosition(particle.XPos - radius, particle.YPos - radius);
                    particles.push_back(particle);
                }
            }
        }

        // Calculations
        for (Particle& particle : particles) {
            double XAccel = 0;
            double YAccel = 0;
            for (const Particle& opParticle : particles) {
                if (particle.id == opParticle.id) continue;

                double deltaX = opParticle.XPos - particle.XPos;
                double deltaY = opParticle.YPos - particle.YPos;
                double XForce = particle.mass * opParticle.mass * gConst / (deltaX * deltaX);
                double YForce = particle.mass * opParticle.mass * gConst / (deltaY * deltaY);

                //        (force)/ (mass       ) * (direction              ) * (mult    )
                XAccel += XForce / particle.mass * (abs(deltaX) / deltaX) * multiplier;
                YAccel += YForce / particle.mass * (abs(deltaY) / deltaY) * multiplier;

                /*// Display
                if(particle.id == 0) {
                    p1p.setString(to_string(XForce) + " " + to_string(YForce));
                } else {
                    p2p.setString(to_string(XForce) + " " + to_string(YForce));
                }*/
            }
            particle.XVel += XAccel * clock.getElapsedTime().asSeconds();
            particle.YVel += YAccel * clock.getElapsedTime().asSeconds();
            particle.XPos += particle.XVel * clock.getElapsedTime().asSeconds();
            particle.YPos += particle.YVel * clock.getElapsedTime().asSeconds();

            float radius = particle.shape.getRadius();
            particle.shape.setPosition(particle.XPos - radius, particle.YPos - radius);
        }

        clock.restart();
        window.clear();
        for (const Particle& particle : particles) {
            window.draw(particle.shape);
        }

        window.display();
    }

    return 0;
}