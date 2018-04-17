//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_PLAYER_H
#define SK_IVER_PLAYER_H


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Diver
{
public:
    // Constructor & Destructor:
    Diver();
    ~Diver();

    // Getters & Setters:
    sf::Texture texture;
    sf::Sprite sprite;
//    enum class Directions{Down, Left, Right, Up};
    sf::Vector2f getSize();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f position);
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f velocity);
    float getMaxSpeed();
//    void setMaxSpeed(float maxSpeed); // should be a constant?
    float getAcceleration();
    void setAcceleration(float acceleration);
    float getDeceleration();
    void setDeceleration(float deceleration);
    float getAnimationFrame();

    // functions:
    //sf::Texture getTexture();
    void setTexture(string filePath);
//    sf::Sprite getSprite();
    void setSprite(); // has no parameters as users Diver.texture, which is already set
    void getInputs(sf::View view);
    float update(sf::Clock clock, float frameCounter, float frameSpeed);
    void draw();
    // others...

private: // should be a singleton?
    sf::Vector2f spriteDimensions;

    map<string, int> directions;

    sf::Vector2i screenSize;

    sf::Vector2i source;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float maxSpeed;
    float acceleration;
    float deceleration;

    float animationFrame;

    void checkOutOfBounds();
};

#endif //SK_IVER_PLAYER_H
