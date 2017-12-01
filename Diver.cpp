//
// Created by William Webster on 15/11/2017.
//

#include <SFML/Graphics.hpp>
#include "Diver.h"
#include <iostream>
#include <cmath>
#include <map>

using namespace std;

// Constructor & Destructor:
Diver::Diver() {
    x = 0;
    y = 0;
    size = 20;
    sf::Texture texture;
    sf::Sprite sprite;
//    enum class Directions{Down, Left, Right, Up}; // defition of a type, not variable
    map<string, int> directions = { {"Down", 0}, // like an array, but rather than an index no, uses a key value (ie, an associative array)
                                    {"Left", 1},
                                    {"Right", 2},
                                    {"Up", 3} };

    sf::Vector2i source(0, directions["Down"]);
    sf::Vector2f position(0.0, 0.0);
    sf::Vector2f velocity(0.0, 0.0);
    maxSpeed = 4.0f;
    acceleration = 0.5f;
    deceleration = 0.98f;

    animationFrame = 100;
}

Diver::~Diver() {};

// Getters & Setters:
int Diver::getX() {
    return x;
}

void Diver::setX(int x) {
    Diver::x = x;
}

int Diver::getY() {
    return y;
}

void Diver::setY(int y) {
    Diver::y = y;
}

int Diver::getSize() {
    return size;
}

void Diver::setSize(int size) {
    Diver::size = size;
}

//sf::Texture Diver::getTexture(){
//    return texture;
//}

void Diver::setTexture(string filePath) {
    //sf::Texture Diver::texture; // object already created in the constructor
    if(!texture.loadFromFile(filePath))
        cout << "ERROR: Could not load diver texture from file path." << endl;
}

//const sf::Sprite &Diver::getSprite() const {
//    return playerImage;
//}

void Diver::setSprite() {
    // should enclose in a try catch for in case texture not already loaded
    sprite.setTexture(texture);
}

// getDirections

sf::Vector2f Diver::getPosition(){
    return position;
}

void Diver::setPosition(sf::Vector2f position) {
    Diver::position = position;
}

sf::Vector2f Diver::getVelocity(){
    return velocity;
}

void Diver::setVelocity(sf::Vector2f velocity) {
    Diver::velocity = velocity;
}

float Diver::getMaxSpeed(){
    return maxSpeed;
}

//void Diver::setMaxSpeed(float maxSpeed) {
//    Diver::maxSpeed = maxSpeed;
//}

float Diver::getAcceleration() {
    return acceleration;
}

void Diver::setAcceleration(float acceleration) {
    Diver::acceleration = acceleration;
}

float Diver::getDeceleration() {
    return deceleration;
}

void Diver::setDeceleration(float deceleration) {
    Diver::deceleration = deceleration;
}

float Diver::getAnimationFrame() {
    return animationFrame;
}

// Functions::
void Diver::getInputs(){
    // vertical movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        source.y = directions["Up"];

        velocity.y -= acceleration; // apply forward acceleration by decrementing y velocity

    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        source.y = directions["Down"];

        velocity.y += acceleration; // apply backward acceleration by incrementing y velocity
    } else
        velocity.y *= deceleration; // decelerate

    // horizontal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        source.y = directions["Right"];

        velocity.x += acceleration; // apply rightward acceleration
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        source.y = directions["Left"];

        velocity.x -= acceleration; // apply leftward acceleration
        // velocity.x -= acceleration * deltaTime.restart().asSeconds();
    } else {
        velocity.x *= deceleration; // else, not moving horizontally, so apply deceleration (why '*='?)
    }
}

void Diver::update(sf::Clock clock, float frameCounter, float frameSpeed) {
    // now that we've updated our velocity, make sure we're not going beyond max speed:
    float actualSpeed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)); // a*a + b*b = c*c

    if (actualSpeed > maxSpeed) // are we going too fast?
        velocity *= maxSpeed / actualSpeed; // scale our velocity down so we are going at the max speed

    // now we have our final velocity, update player's position
    position += velocity; // TODO update class
    // TODO extra function call to catch player going off screen

    // needs to be moved to it's own class VVV

    // "* clock.restart().asSeconds" keeps the animation consistent through realtime, rather than depending on cpu's clockspeed
    frameCounter += frameSpeed * clock.restart().asSeconds();
    // if 500 frames have passed, cycle through to next animation
    if (frameCounter >= getAnimationFrame()) {
        // animation of sprite through SS images, based on which direction facing
        source.x++;
        if (texture.getSize().x <= source.x * 256)
            source.x = 0;

        frameCounter = 0;
    }

    sprite.setTextureRect(sf::IntRect(source.x * 256, source.y * 256, 256, 256));
    sprite.setPosition(position);
}