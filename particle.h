#ifndef APP2_SIMULATION_PARTICLE_H
#define APP2_SIMULATION_PARTICLE_H

#endif //APP2_SIMULATION_PARTICLE_H
#include <SFML/Graphics.hpp>
#include <iostream>

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

// Set radius and origin based off of that
void Particle::Initialize() {
    shape.setRadius((float)abs(magnitude));
    shape.setOrigin((float)magnitude, (float)magnitude);
}

// Move it
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
        double distanceSquared = pow(sqrt(XDelta * XDelta + YDelta * YDelta), 2);
        // Sign (positive / negative) of the difference
        int XSign = (int)(abs(XDelta) / XDelta);
        int YSign = (int)(abs(YDelta) / YDelta);

        double XForce = particle.magnitude * magnitude * multiplier * XDelta / pow(distanceSquared, 3/2);
        double YForce = particle.magnitude * magnitude * multiplier * XDelta / pow(distanceSquared, 3/2);

        XAcc += XForce / magnitude;
        YAcc += YForce / magnitude;
    }
}




