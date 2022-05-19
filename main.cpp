#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class lilDude {
public:
    int state;
    int mass;
    int velocity;
};

int main()
{
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