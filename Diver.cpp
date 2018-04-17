//
// Created by William Webster on 15/11/2017.
//

#include <SFML/Graphics.hpp>
#include "Diver.h"
#include <cmath>
#include <map>

using namespace std;

extern sf::RenderWindow window;

// Constructor & Destructor:
Diver::Diver() {
    setTexture("Resources/Images/newDiver_spritesheet3.png");
    setSprite();

    spriteDimensions.x = sprite.getLocalBounds().width / 4;
    spriteDimensions.y = sprite.getLocalBounds().height / 4;

    sprite.setScale(5, 5); // at this point globalBounds (560) becomes 5 times as much as localBounds (112):
    cout << "spriteDimensions.x = " <<  spriteDimensions.x << ", sprite.getLocalBounds().width = " << sprite.getLocalBounds().width << ", sprite.getGlobalBounds().width = " << sprite.getGlobalBounds().width << endl;

//    enum class Directions{Down, Left, Right, Up}; // defition of a type, not variable
    map<string, int> directions = { {"Down", 0}, // like an array, but rather than an index no, uses a key value (ie, an associative array)
                                    {"Left", 1},
                                    {"Right", 2},
                                    {"Up", 3} };

    /*source(0, directions["Down"]);
    position(0.0, 0.0);
    velocity(0.0, 0.0);*/

    screenSize.x = window.getSize().x;
    screenSize.y = window.getSize().y;

    position.x = (screenSize.x - sprite.getGlobalBounds().width) / 2;
    position.y = (screenSize.y - sprite.getGlobalBounds().height) / 2;

    maxSpeed = 4.0f;
    acceleration = 0.5f;
    deceleration = 0.98f;

    animationFrame = 500; // or 100?
}

Diver::~Diver() {} //= default;

// Getters & Setters:
void Diver::setTexture(string filePath) {
    //sf::Texture Diver::texture; // object already created in the constructor
    if(!texture.loadFromFile(filePath))
        cout << "ERROR: Could not load diver texture from file path." << endl;
}

void Diver::setSprite() {
    // should enclose in a try catch for in case texture not already loaded
    sprite.setTexture(texture);
}

sf::Vector2f Diver::getSize(){
//    cout << "spriteDimensions.x: " << spriteDimensions.x << ", sprite.globalBounds().width: " << sprite.getGlobalBounds().width << endl;
    return spriteDimensions;
//    return sprite.getGlobalBounds().type;
}

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
void Diver::getInputs(sf::View view){
    // vertical movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//        source.y = directions["Up"];
        source.y = 3;

        velocity.y -= acceleration; // apply forward acceleration by decrementing y velocity
//         view.zoom(0.99f);   // zooms in
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//        source.y = directions["Down"];
        source.y = 0;

        velocity.y += acceleration; // apply backward acceleration by incrementing y velocity
//         view.zoom(1.01f);   // zooms in todo return view/figure out best way of changing variable
    } else
        velocity.y *= deceleration; // decelerate

    // horizontal movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) or sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//        source.y = directions["Right"];
        source.y = 2;
        //background.setRotation(

        velocity.x += acceleration; // apply rightward acceleration
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) or sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//        source.y = directions["Left"];
        source.y = 1;

        velocity.x -= acceleration; // apply leftward acceleration
        // velocity.x -= acceleration * deltaTime.restart().asSeconds();
    } else {
        velocity.x *= deceleration; // else, not moving horizontally, so apply deceleration (why '*='?)
    }
}

void Diver::checkOutOfBounds(){
    if(position.x < 0)
        position.x = 0;
    else if (position.x + sprite.getGlobalBounds().width > screenSize.x )
        position.x = screenSize.x - sprite.getGlobalBounds().width;

    if(position.y < 0)
        position.y = 0;
    else if (position.y + sprite.getGlobalBounds().height > screenSize.y )
        position.y = screenSize.y - sprite.getGlobalBounds().height;
}

float Diver::update(sf::Clock clock, float frameCounter, float frameSpeed) {
    // now that we've updated our velocity, make sure we're not going beyond max speed:
    float actualSpeed = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)); // a*a + b*b = c*c

    if (actualSpeed > maxSpeed) // are we going too fast?
        velocity *= maxSpeed / actualSpeed; // scale our velocity down so we are going at the max speed

    // now we have our final velocity, update player's position
    position += velocity; // TODO update class

    checkOutOfBounds(); // check if player is outside the bounds

    // needs to be moved to it's own class VVV

    // "* clock.restart().asSeconds" keeps the animation consistent through realtime, rather than depending on cpu's clockspeed
    frameCounter += frameSpeed * clock.restart().asSeconds(); //clock.getElapsedTime().asMicroseconds();

    // if 500 frames have passed, cycle through to next animation
    if (frameCounter >= getAnimationFrame() + 100000) {
        // animation of sprite through SS images, based on which direction facing
        source.x++;
        if (texture.getSize().x <= source.x * spriteDimensions.x)
            source.x = 0;

        frameCounter = 0;
    }

    sprite.setTextureRect(sf::IntRect(source.x * spriteDimensions.x, source.y * spriteDimensions.y, spriteDimensions.x, spriteDimensions.y));
    sprite.setPosition(position);

    return frameCounter;
}

void Diver::draw(){
    window.draw(sprite);
}