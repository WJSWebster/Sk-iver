//
// Created by William Webster on 06/12/2017.
//

#include <SFML/Graphics.hpp>
#include "Background.h"

using namespace std;

Background::Background(sf::RenderWindow& window) {
    setImage("Resources/Images/skydiving_placeholder.jpg");
    setSprite();

    fallVelocity = 0;
    fallAcceleration = 0.0000002;

    windowSize.x = window.getSize().x;
    windowSize.y = window.getSize().y;

    sf::Vector2f spriteDimensions(sprite.getLocalBounds().width, sprite.getLocalBounds().height);

    // stretches image to window size
    sf::Vector2f spriteScale(windowSize.x / spriteDimensions.x, windowSize.y / spriteDimensions.y);
    sprite.setScale(spriteScale);

    sf::Vector2f spriteCentre(sprite.getLocalBounds().width / 2,  sprite.getLocalBounds().height / 2);

    sprite.setOrigin(spriteCentre); // from now on, the 'origin' of this image will be it's centre, meaning all transformations use the centre as it's anchor point
    sprite.setPosition(windowSize.x / 2, windowSize.y / 2);
}

Background::~Background() {
}

void Background::setImage(string filePath) {
    if (!texture.loadFromFile(filePath))
        cout << "ERROR: Could not load diver texture from file path." << endl;
}

void Background::setSprite() {
    // should enclose in a try catch for in case texture not already loaded
    sprite.setTexture(texture);
}

void Background::setRotation(float rotation) {
//    float newRotation = sprite.getRotation() + rotation;

//    if (newRotation < 0)
//        newRotation += 360;
//    else if (newRotation > 360)
//        newRotation -= 360;

    //sprite.setRotation(newRotation);
    sprite.rotate(rotation);
}

void Background::update(){
//    setRotation(1);
    fallVelocity += fallAcceleration;
    sf::Vector2f newScale(sprite.getScale().x + fallVelocity, sprite.getScale().y + fallVelocity);
    sprite.setScale(newScale);
}

void Background::draw(sf::RenderWindow& window){
    window.draw(sprite);
}
