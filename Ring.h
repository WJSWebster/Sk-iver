//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_RING_H
#define SK_IVER_RING_H

#include <SFML/Graphics.hpp>
#include "Diver.h"
#include "Particle.h"

class Ring
{
public:
    Ring();

    sf::CircleShape circle;

    int getStage();
    void incrementStage();

    float getX() const;
    void setX(int x);

    float getY() const;
    void setY(int y);

    double getSize() const;
    void setSize(float size);

    float getCurrSize() const;
    void setCurrSize(float currSize);

    int getPoints();
    int incPoints(int pointInc);

    void loadHitSound();
    void playHitSound();

    void loadMissSound();
    void playMissSound();

    int update(Diver player);
    void draw();

private:
    int stage;
    int points;

    float x;
    float y;

    float size;

    sf::Color outlineColor;

    bool ringHit;
    Particle particle;
    vector<Particle> dots;
    vector<sf::Vertex> specks;
    vector<Particle> generateDots(int);
    vector<sf::Vertex> generateSpecks(vector<Particle>);


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
