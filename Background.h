//
// Created by William Webster on 06/12/2017.
//

#ifndef SK_IVER_BACKGROUND_H
#define SK_IVER_BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Background {
public:
    explicit Background(sf::RenderWindow &window);

    ~Background();

    void setRotation(float rotation);

    void draw(sf::RenderWindow &window);

    void update();

private:
    sf::Vector2i windowSize;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f spriteScale;

    float fallVelocity;
    float fallAcceleration;

    void setImage(std::string filePath);
    void setSprite();
};


#endif //SK_IVER_BACKGROUND_H
