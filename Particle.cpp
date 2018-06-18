//
// Created by William Webster on 17/06/2018.
//

#include "Particle.h"
#include <SFML/Graphics.hpp>
#include <math.h>

void Particle::update()
{
    velocity = velocity + acceleration;
    position = position + velocity;
}

float Particle::distance(float x1, float x2, float y1, float y2)
{
    float x = x2 - x1;
    float y = y2 - y1;

    float distance = sqrt((x * x) + (y * y));

    return distance;
}
