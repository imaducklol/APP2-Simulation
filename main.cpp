#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;

class Particle {
public:
    int id{};
    int state;
    double mass;
    double vel;
    double dir;
    double XPos;
    double YPos;

    explicit Particle(int s = 0, double m = 10, double v = 0, double d = 0, double x = 0, double y = 0) {
        state = s;
        mass = m;
        vel = v;
        dir = d;
        XPos = x;
        YPos = y;
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

    /*cout << "velocity\n";
    cin >> input;
    particle.vel = input;

    cout << "direction\n";
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

    // Screen Setup
    int XRes = 400;
    int YRes = 400;

    sf::RenderWindow window(sf::VideoMode(XRes, YRes), "Simulation");

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}