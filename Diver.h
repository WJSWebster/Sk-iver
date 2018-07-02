//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_PLAYER_H
#define SK_IVER_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>

class Diver
{
public:
    // Constructor & Destructor:
    Diver(sf::Vector2u windowSize);
    ~Diver();

    // Getters & Setters:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f getSize();
    sf::Vector2f getPosition();

    float getAnimationFrame();

    // functions:
    void setTexture(const char *filePath);
    void setSprite(); // has no parameters as users Diver.texture, which is already set
    void getInputs();
    float update(sf::Clock clock, float frameCounter, float frameSpeed);
    void draw(sf::RenderWindow &window);

private:
    sf::Vector2i screenSize;

    sf::Vector2f spriteDimensions;
    // like an array, but rather than an index no, uses a key value (ie, an associative array)
    std::map<std::string, int> directions  = { {"Down", 0},
                                     {"Left", 1},
                                     {"Right", 2},
                                     {"Up", 3} };
    sf::Vector2i source;
    sf::Vector2f position, velocity;
    float maxSpeed = 4.0f;
    float acceleration = 0.5f;
    float deceleration = 0.98f;

    float animationFrame = 500;

    void checkOutOfBounds();
};

#endif //SK_IVER_PLAYER_H
