#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Particle {
public:
    int id{};
    int state;
    double mass;
    double XVel;
    double YVel;
    double XPos;
    double YPos;
    sf::CircleShape shape;

    explicit Particle(int istate = 0, double imass = 10, double ixvel = 0, double yvel = 0, double ixpos= 0, double iypos = 0) {
        state = istate;
        mass = imass;
        XVel = ixvel;
        YVel = yvel;
        XPos = ixpos;
        YPos = iypos;
    }
};

void AddParticle(vector<Particle> &particles) {
    Particle particle;
    double input;

    particle.id = (int)particles.size();

    cout << "dynamic(0), static(1), or mouse controlled(2)\n";
    cin >> input;
    particle.state = (int)input;

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

void ListParticles(const vector<Particle>& particles) {
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
    double gConst = 6.6743 * pow(10, 2);
    double rad2dec = 180 / atan(1) * 4;
    vector<Particle> particles;

    while (true) {
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
    programStart:

    // Initialize the actual circle shape for sfml, binding the size
    for (Particle& particle : particles) {
        double x = particle.mass;
        /*if (x < -100) {
            particle.shape.setRadius(abs(.05 * x - 95));
        } else if (x >= -100 && x <= 100) {
            particle.shape.setRadius(abs(x));
        } else if (x > 100) {
            particle.shape.setRadius(abs(.05 * x + 95));
        }*/
        particle.shape.setRadius(abs(x));

        particle.shape.setPosition(particle.XPos, particle.YPos);
    }

    // Screen Setup
    int XRes = 400;
    int YRes = 400;
    sf::RenderWindow window(sf::VideoMode(XRes, YRes), "Simulation");

    while (window.isOpen()) {
        sf::Event event{};
        sf::Clock clock;
        // Closing
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculations
        for (Particle particle : particles) {
            for (Particle opParticle : particles) {
                if (particle.id == opParticle.id) continue;

                double deltaX = opParticle.XPos - particle.XPos;
                double deltaY = opParticle.YPos - particle.YPos;
                double XAccel = particle.mass * opParticle.mass * gConst / (deltaX * deltaX);
                double YAccel = particle.mass * opParticle.mass * gConst / (deltaY * deltaY);

                particle.XVel += XAccel * clock.getElapsedTime().asSeconds();
                particle.YVel += XAccel * clock.getElapsedTime().asSeconds();
            }
        }


        clock.restart();
        window.clear();
        for (Particle particle : particles) {
            window.draw(particle.shape);
        }
        window.display();
    }

    return 0;
}