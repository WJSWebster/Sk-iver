//
// Created by William Webster on 17/06/2018.
//

#ifndef SK_IVER_PARTICLE_H
#define SK_IVER_PARTICLE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


class Particle {
public:
    // Variables:
    sf::Vector2f acceleration, velocity, position  = sf::Vector2f(0, 0);

    // Functions:
    void update();

    float distance(float x1, float x2, float y1, float y2);
};


#endif //SK_IVER_PARTICLE_H
