//
// Created by William Webster on 26/06/2018.
//

#ifndef SK_IVER_PARTICLES_H
#define SK_IVER_PARTICLES_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Particle.h"

class Particles {
public:
//    Particles(int range, sf::Vector2f ringPos);
    ~Particles();

    // standin for constructor so class can be instantiated and particles generate at separate times in Ring:
    void generateParticles(int range, sf::Vector2f ringPos);

    void update(sf::Color colour);
    void draw(sf::RenderWindow &window);

private:
    std::vector<Particle> particles;
    std::vector<sf::Vertex> vertices;
};


#endif //SK_IVER_PARTICLES_H
