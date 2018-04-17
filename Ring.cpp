//
// Created by William Webster on 15/11/2017.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <ctime>
#include <SFML/Audio.hpp>
#include "Ring.h"
#include "Diver.h"

using namespace std;

extern sf::RenderWindow window;

Ring::Ring() {
    stage = 0;
    points = 0;

    srand((unsigned int)time(NULL)); // makes true random (using seed based on curr time)

    x = (float) ((rand() % (window.getSize().x - 325)) + 162.5); // so they dont upscale to be outside of the screen dimensions
    y = (float) ((rand() % (window.getSize().y - 325)) + 162.5);

    cout << "x: " << x << ", y: " << y << endl;

    setSize(150);
    setCurrSize(0); // sets the current radius to 0, and reassigns circle's origin appropriately
    circle.setPosition(x, y);


    outlineColor = sf::Color::Yellow;
    outlineColor.a = 0;

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(outlineColor);
    circle.setPointCount(10);
    circle.setOutlineThickness(20);
}

int Ring::getStage() {
    return stage;
}

void Ring::incrementStage() {
    stage = stage + 1;
}

int Ring::getPoints() {
    return points;
}

int Ring::incPoints(int pointInc = 1) {
    points += pointInc;
}

float Ring::getX() const {
    return x;
}

void Ring::setX(int x) {
    Ring::x = x;
    circle.setPosition(x, y);
}

float Ring::getY() const {
    return y;
}

void Ring::setY(int y) {
    Ring::y = y;
    circle.setPosition(x, y);
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
    resetOrigin();
}

void Ring::resetOrigin() {
    // circle.setOrigin(
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

void Ring::loadHitSound() {
    if(!hitBuffer.loadFromFile("Resources/Sounds/jump.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        cout << "ERROR: could not load audio file from file path" << endl;

    hitSound.setBuffer(hitBuffer);
}

void Ring::playHitSound() {
    hitSound.play();
}

void Ring::loadMissSound() {
    if(!missBuffer.loadFromFile("Resources/Sounds/zap.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        cout << "ERROR: could not load audio file from file path" << endl;

    missSound.setBuffer(missBuffer);
}

void Ring::playMissSound() {
    missSound.play();
}

void Ring::update(Diver player){
    float tempSize = getCurrSize();

    switch(stage) {
        case 0 :
            tempSize += 0.5;
            setCurrSize(tempSize);

            if (circle.getOutlineColor().a < 255) { // makes ring gradually more transparent
                makeMoreOpaque();
            }

            if (getCurrSize() >= size) // if circle has reached full size
                incrementStage();

            break;

        case 1 : // when the ring is in the stage of diving through
            if ((player.getPosition().x >= circle.getPosition().x) &&
                    (player.getPosition().y >= circle.getPosition().y) &&
                    (player.getPosition().x + player.getSize().x <= circle.getPosition().x + circle.getLocalBounds().width) &&
                    (player.getPosition().y + player.getSize().y <= circle.getPosition().y + circle.getLocalBounds().height) )
            {
                outlineColor = sf::Color::Green;

                loadHitSound();
                playHitSound();

                incPoints();
            }
            else if (player.sprite.getGlobalBounds().intersects(circle.getGlobalBounds()))
            {
                outlineColor = sf::Color::Magenta;

                loadHitSound();
                playHitSound();
            }
            else
            {
                outlineColor = sf::Color::Red;

                loadMissSound();
                playMissSound();
            }

            incrementStage();

            break;

        case 2 : // when the ring has flown past the diver
            tempSize += 1.5;
            setCurrSize(tempSize);

            if (outlineColor.b < 252){
                makeMoreBlue();
            }

            if (circle.getOutlineColor().a >= 2) { // makes ring gradually more transparent
                makeMoreTransparent();
            }
            else
                incrementStage();

            break;

        default:
            break;
    }
}

void Ring::makeMoreOpaque(){
    outlineColor.a += ceil(0.85); // outlineColor.a is type int
    circle.setOutlineColor(outlineColor);
}

void Ring::makeMoreTransparent(){
    outlineColor.a -= 2; // outlineColor.a is type int
    circle.setOutlineColor(outlineColor);
    // cout << static_cast<int>(circle.getOutlineColor().a);
}

void Ring::makeMoreBlue(){
    outlineColor.b += 1;
    circle.setOutlineColor(outlineColor);
}

void Ring::draw(){
    window.draw(circle);
}