//
// Created by William Webster on 26/06/2018.
//

#ifndef SK_IVER_PARTICLES_H
#define SK_IVER_PARTICLES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <SFML/Audio.hpp>
#include "Particle.h"

class Particles {
public:
//    void Particles(int num, sf::CircleShape circle);
    void generateParticles(int range, sf::CircleShape circle); // standin for constructor so class can be instantiated and particles generate at separate times in Ring

    void update(sf::Color colour);
    void draw();

private:
    std::vector<Particle> particles;
    std::vector<sf::Vertex> vertices;
};


#endif //SK_IVER_PARTICLES_H
