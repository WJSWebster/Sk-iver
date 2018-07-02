//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_RING_H
#define SK_IVER_RING_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include "Particles.h"
#include "Diver.h"

class Ring
{
public:
    explicit Ring(sf::Vector2u windowSize);
    ~Ring();

    sf::CircleShape circle;

    int getStage();

    int update(Diver player);
    void draw(sf::RenderWindow &window);

private:
    int stage = 0;

    sf::Vector2f position;

    float size = 150;

    sf::Color outlineColor = sf::Color::Yellow;

    bool ringHit = false;

    Particles particles;

    sf::SoundBuffer hitBuffer, missBuffer;
    sf::Sound hitSound, missSound;


    void incrementStage();

    float getCurrSize() const;
    void setCurrSize(float currSize);

    void loadHitSound();
    void playHitSound();

    void loadMissSound();
    void playMissSound();

    void makeMoreTransparent();
    void makeMoreOpaque();

    void makeMoreBlue();

    void resetOrigin();
};

#endif //SK_IVER_RING_H
