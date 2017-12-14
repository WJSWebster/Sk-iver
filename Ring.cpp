//
// Created by William Webster on 15/11/2017.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Ring.h"

using namespace std;

Ring::Ring() {
    orgX = rand() % 920;
    orgY = rand() % 1080;
    size = 150;

    currX = (float) (orgX + (size * 1.1359465));
    currY = (float) (orgY + (size * 1.1359465));

    outlineColor = sf::Color::Yellow;
    outlineColor.a = 0;

//    circle.setRadius(size);
    circle.setRadius(0);
    circle.setPointCount(16);
    circle.setPosition(currX, currY);

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(20);
    circle.setOutlineColor(outlineColor);

    cout << "circle orgX & orgY: " << circle.getPosition().x << " " << circle.getPosition().y << endl;
}

int Ring::getX() const {
    return orgX;
}

void Ring::setX(int x) {
    Ring::orgX = x;
    circle.setPosition(x, orgY);
}

int Ring::getY() const {
    return orgY;
}

void Ring::setY(int y) {
    Ring::orgY = y;
    circle.setPosition(orgX, y);
}

double Ring::getSize() const {
    return size;
}

void Ring::setSize(float size) {
    Ring::size = size;
}

float Ring::getCurrSize() const {
    return circle.getRadius();
}

void Ring::setCurrSize(float currSize) {
    circle.setRadius(currSize);
}

void Ring::update(){
    float tempSize = circle.getRadius();

    if (tempSize < getSize()){
        tempSize += 0.5;
        circle.setRadius(tempSize);

        currX -= (float) 0.56797325; // TODO needs to be less hard coded
        currY -= (float) 0.56797325; // ((size(150) * 1.1359465) / (size(150) / 0.5))
        circle.setPosition(currX, currY);
    }

    if (circle.getOutlineColor().a < 255){
        outlineColor.a += ceil(0.85);  // outlineColor.a is type int
        circle.setOutlineColor(outlineColor);
    }

    if (circle.getRadius() >= 150){ // if circle has reached full size
        tempSize += 5;
        circle.setRadius(tempSize);

        currX -= (float) (size * 1.1359465) / (size / 5); // TODO This still needs to be less hard-coded
        currY -= (float) (size * 1.1359465) / (size / 5);
        circle.setPosition(currX, currY);

        // TODO if diver within outline (else outlineColour = sf::Color::red;
        outlineColor = sf::Color::Green;
        if (outlineColor.b < 255){ // TODO why doesnt this work?!
            outlineColor.b++;
        }
        circle.setOutlineColor(outlineColor);

    }
}