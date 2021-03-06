//
// Created by William Webster on 26/06/2018.
//

#include "Particles.h"

void Particles::generateParticles(int range, sf::Vector2f ringPos) {
    particles.clear(); // added security incase called multiple times
    float radius, theta, x, y;

    for (int i = 0; i < range; i++)
    {
        Particle temp;

        // How quickly the particles expand outwards
        radius = rand() % 3000;
        radius = static_cast<float>((radius / 1000) + 0.005);

        // the number of possible angles that the particles could fly out at
        theta = rand() % 360;

        x = radius * cos(theta);
        y = radius * sin(theta);

        temp.velocity = sf::Vector2f(x, y);
        temp.position = ringPos;
        std::cout << "Particles: ringPos.x="<< ringPos.x << ", ringPos.y=" << ringPos.y << std::endl;

        particles.push_back(temp); // places temp into the vector
    }
}

Particles::~Particles() = default;

// draw a vertex at the position of each particle
void Particles::update(sf::Color ringColour)
{
    vertices.clear();

    for (auto &particle : particles)
    {
        particle.update();

        sf::Vertex temp;
        temp.position = particle.position;
        temp.color = ringColour;

        vertices.push_back(temp);
    }
}

void Particles::draw(sf::RenderWindow &window)
{
    window.draw(&vertices[0], vertices.size(), sf::Points);
}
