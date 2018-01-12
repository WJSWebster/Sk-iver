//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_RING_H
#define SK_IVER_RING_H

#include <SFML/Graphics.hpp>
#include "Diver.h"

class Ring
{
public:
    Ring();

    sf::CircleShape circle;

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    double getSize() const;

    void setSize(float size);

    float getCurrSize() const;

    void setCurrSize(float currSize);

    void update(Diver player);

    void draw(sf::RenderWindow &window);

private:
    int stage;

    int orgX;
    int orgY;
    float currX;
    float currY;

    float size;

    sf::Color outlineColor;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
    sf::SoundBuffer missBuffer;
    sf::Sound missSound;

    void makeMoreTransparent();

    void makeMoreOpaque();

    void makeMoreBlue();
};

#endif //SK_IVER_RING_H
