//
// Created by William Webster on 06/12/2017.
//

#ifndef SK_IVER_BACKGROUND_H
#define SK_IVER_BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Background {
public:
    explicit Background(sf::Vector2u windowSize);
//    ~Background();

    void setRotation(float rotation);

    void update();
    void draw(sf::RenderWindow &window);

private:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f spriteScale;

    float fallVelocity = 0;
    float fallAcceleration = 0.0000002;

    void setImage(std::string filePath);
    void setSprite();


};


#endif //SK_IVER_BACKGROUND_H
