//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_RING_H
#define SK_IVER_RING_H

#include <SFML/Graphics.hpp>

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

    void update();

private:
    int orgX;
    int orgY;
    float currX;
    float currY;

    float currSize;
    float size;

    sf::Color outlineColor;
};

#endif //SK_IVER_RING_H
