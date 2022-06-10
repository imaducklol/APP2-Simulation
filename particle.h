#ifndef APP2_SIMULATION_PARTICLE_H
#define APP2_SIMULATION_PARTICLE_H

#endif //APP2_SIMULATION_PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle {
public:
    int id;
    int state;
    double magnitude;
    double XAcc;
    double YAcc;
    double XVel;
    double YVel;
    sf::CircleShape shape;

    Particle (int i, int s, int m);
    void Initialize();
    void Calculate(std::vector<Particle> &, double);
    void Move(double, double);
    void Set(double, double);

};

Particle::Particle(int i, int s, int m) {
    id = i;
    state = s;
    magnitude = m;
    XAcc = 0;
    YAcc = 0;
    XVel = 0;
    YVel = 0;
}

void Particle::Initialize() {
    shape.setRadius((float)abs(magnitude));
    shape.setOrigin((float)magnitude, (float)magnitude);
}

void Particle::Move(double x, double y) {
    shape.move((float)x, (float)y);
}

void Particle::Set(double x, double y) {
    shape.setPosition((float)x, (float)y);
}

void Particle::Calculate(std::vector <Particle> & particles, double multiplier) {
    // Reset
    XAcc = YAcc = 0;
    for (const Particle& particle : particles) {
        // Don't calculate on self
        if (id == particle.id) continue;

        // Distance between the particles that we are calculating on
        double XDelta = particle.shape.getPosition().x - shape.getPosition().x;
        double YDelta = particle.shape.getPosition().y - shape.getPosition().y;
        // Sign (positive / negative) of the difference
        int XSign = (int)(abs(XDelta) / XDelta);
        int YSign = (int)(abs(YDelta) / YDelta);

        double XForce = particle.magnitude * magnitude / XDelta / XDelta * multiplier * XSign;
        double YForce = particle.magnitude * magnitude / YDelta / YDelta * multiplier * YSign;

        XAcc += XForce / magnitude;
        YAcc += YForce / magnitude;
    }
}




