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

Ring::Ring() {
    stage = 0;

    srand((size_t)time(NULL)); // makes true random (using seed based on curr time)
    orgX = rand() % 1920; // todo needs to be soft coded based on screen size
    orgY = rand() % 1280;

    cout << "orgX: " << orgX << ", orgY: " << orgY << endl;

    size = 150;

    currX = (float) (orgX + (size * 1.1359465));
    currY = (float) (orgY + (size * 1.1359465)); // todo WHY??

    // need to setOrigin(currX, currY) here
//    circle.setOrigin(circle.getPosition().x, circle.getPosition().x);

    outlineColor = sf::Color::Yellow;
    outlineColor.a = 0;

//    circle.setRadius(size);
    circle.setRadius(0);
    circle.setPointCount(10);
    circle.setPosition(currX, currY);
//    circle.setOrigin(currX + (circle.getRadius() / 2), currY + (circle.getRadius() / 2));

    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(20);
    circle.setOutlineColor(outlineColor);

    // 'once and only once' code smell -> todo: make a setSound function?

    // sf::Sound hitSound & missSound defined in header

    if(!hitBuffer.loadFromFile("Resources/Sounds/jump.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        cout << "ERROR: could not load audio file from file path" << endl;

    if(!missBuffer.loadFromFile("Resources/Sounds/zap.wav")) // if audio file is longer than 30 secs, should probs just stream as Music instead
        cout << "ERROR: could not load audio file from file path" << endl;

    hitSound.setBuffer(hitBuffer);
    missSound.setBuffer(missBuffer);

    circle.setOrigin(circle.getPosition().x, circle.getPosition().x);
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

void Ring::update(Diver player){
    float tempSize = circle.getRadius();
//    circle.setOrigin(currX + (tempSize / 2), currY + (tempSize / 2));


    switch(stage) {
        case 0 :
            tempSize += 0.5;
            circle.setRadius(tempSize);

            currX -= (float) 0.56797325; // TODO needs to be less hard coded
            currY -= (float) 0.56797325; // ((size(150) * 1.1359465) / (size(150) / 0.5))
            circle.setPosition(currX, currY);

            if (circle.getOutlineColor().a < 255) { // makes ring gradually more transparent
                makeMoreOpaque();
            }

            if (circle.getRadius() >= size) // if circle has reached full size
                stage = 1;
            break;

        case 1 : // when the ring is in the stage of diving through
            // if player x & y is within ring's dimensions
                // do something
            cout << "size: " << size << ", circle.getLocalBounds(): " << circle.getLocalBounds().width << ", circle.getGlobalBounds(): " << circle.getGlobalBounds().width << endl;

            if ((player.getPosition().x >= circle.getPosition().x) &&
                    (player.getPosition().y >= circle.getPosition().y) &&
                    (player.getPosition().x + player.getSize().x <= circle.getPosition().x + circle.getLocalBounds().width) &&
                    (player.getPosition().y + player.getSize().y <= circle.getPosition().y + circle.getLocalBounds().height) )
            {
                outlineColor = sf::Color::Green;
                hitSound.play();
                // increment player's score
            }
            else {
                outlineColor = sf::Color::Red;
                missSound.play();
            }

            stage = 2;

            break;

        case 2 : // when the ring has flown past the diver
//            tempSize += 5;
            tempSize ++;
            tempSize += 0.5;
            circle.setRadius(tempSize);

            currX -= (float) (size * 1.1359465) / (size / 5); // TODO This still needs to be less hard-coded
            currY -= (float) (size * 1.1359465) / (size / 5);
            circle.setPosition(currX, currY);

            // TODO if diver within outline (else outlineColour = sf::Color::red;
            if (outlineColor.b < 252){ // TODO why doesnt this work?!
                makeMoreBlue();
            }

            if (circle.getOutlineColor().a >= 2) { // makes ring gradually more transparent
                makeMoreTransparent();
            }
            else
                // destructor call

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
    outlineColor.b += 4;
    circle.setOutlineColor(outlineColor);
}

void Ring::draw(sf::RenderWindow& window){
    window.draw(circle);
}