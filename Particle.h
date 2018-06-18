//
// Created by William Webster on 17/06/2018.
//

#ifndef SK_IVER_PARTICLE_H
#define SK_IVER_PARTICLE_H

#include <SFML/Graphics.hpp>
#include <stdio.h>


class Particle {
public:
    // Variables:
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    sf::Vector2f position;

    // Functions:
    // Constructor
    Particle()
    {
        acceleration = sf::Vector2f(0, 0);
        velocity     = sf::Vector2f(0, 0);
        position     = sf::Vector2f(0, 0);
    }

    void update();

    float distance(float x1, float x2, float y1, float y2);
};


#endif //SK_IVER_PARTICLE_H
