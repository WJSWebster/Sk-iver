//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_RING_H
#define SK_IVER_RING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <SFML/Audio.hpp>
#include "Particles.h"
#include "Diver.h"

extern sf::RenderWindow window;

class Ring
{
public:
    Ring();
    ~Ring();

    sf::CircleShape circle;

    int getStage();
    void incrementStage();

    float getCurrSize() const;
    void setCurrSize(float currSize);

    void loadHitSound();
    void playHitSound();

    void loadMissSound();
    void playMissSound();

    int update(Diver player);
    void draw();

private:
    int stage = 0;

    float x;
    float y;

    float size = 150;

    sf::Color outlineColor = sf::Color::Yellow;

    bool ringHit = false;

    Particles particles;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
    sf::SoundBuffer missBuffer;
    sf::Sound missSound;

    void makeMoreTransparent();

    void makeMoreOpaque();

    void makeMoreBlue();

    void resetOrigin();
};

#endif //SK_IVER_RING_H
