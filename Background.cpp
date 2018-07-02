//
// Created by William Webster on 06/12/2017.
//

#include "Background.h"

Background::Background(sf::Vector2u windowSize) {
    setImage("Resources/Images/skydiving_placeholder.jpg");
    setSprite();

    sf::Vector2f spriteDimensions(sprite.getLocalBounds().width, sprite.getLocalBounds().height);

    // stretches image to window size
    spriteScale.x = windowSize.x / spriteDimensions.x;
    spriteScale.y = windowSize.y / spriteDimensions.y;
    sprite.setScale(spriteScale);

    sf::Vector2f spriteCentre(sprite.getLocalBounds().width / 2,  sprite.getLocalBounds().height / 2);

    sprite.setOrigin(spriteCentre); // from now on, the 'origin' of this image will be it's centre, meaning all transformations use the centre as it's anchor point
    sprite.setPosition(windowSize.x / 2, windowSize.y / 2);
}

void Background::setImage(std::string filePath) {
    if (!texture.loadFromFile(filePath))
        std::cout << "ERROR: Could not load diver texture from file path." << std::endl;
}

void Background::setSprite() {
    // should enclose in a try catch for in case texture not already loaded
    sprite.setTexture(texture);
}

void Background::setRotation(float rotation) {
    sprite.rotate(rotation);
}

void Background::update(){
    fallVelocity += fallAcceleration;
    sf::Vector2f newScale(sprite.getScale().x + fallVelocity, sprite.getScale().y + fallVelocity);
    sprite.setScale(newScale);
}

void Background::draw(sf::RenderWindow &window){
    window.draw(sprite);
}
