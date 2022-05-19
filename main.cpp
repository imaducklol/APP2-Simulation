#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;

class Particle {
public:
    int id;
    int state;
    double mass;
    double velocity;
    double direction;
    Particle(int s = 0, double m = 10, double v = 0, double d = 0) {
        state = s;
        mass = m;
        velocity = v;
        direction = d;
    }

};

void ListParticles(const vector<Particle>& particles) {
    if (particles.size() == 0) cout << "None yet" << endl;
    else
    for (Particle particle : particles) {
        cout <<
        particle.id    << endl <<
        particle.state << endl <<
        particle.mass  << endl << endl;
    }
}

void AddParticle(vector<Particle> *particles) {
    Particle particle;
    double input;

    particle.id = particles->size();

    cout << "dynamic(0), static(1), or mouse controlled(2)\n";
    cin >> input;
    particle.state = input;

    cout << "mass\n";
    cin >> input;
    particle.mass = input;

    cout << "velocity\n";
    cin >> input;
    particle.velocity = input;

    cout << "dynamic(0), static(1), or mouse controlled(2)\n";
    cin >> input;
    particle.direction = input;

    particles->push_back(particle);
}

int main() {
    // Particle setup
    double gConst = 6.6743 * pow(10, 2);
    vector<Particle> particles;

    while (true) {
        int input;
        cout << "Add Particle (1), list particles (2), run simulation (3)\n";
        cin >> input;

        switch (input) {
            case 1: {

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

    sf::RenderWindow window(sf::VideoMode(200, 200), "Simulation");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}