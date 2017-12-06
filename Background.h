//
// Created by William Webster on 06/12/2017.
//

#ifndef SK_IVER_BACKGROUND_H
#define SK_IVER_BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Background {
public:
    Background();
    virtual ~Background();

    sf::Sprite sprite;

private:
    sf::Texture texture;

    void setImage(std::string filePath);
    void setSprite();
};


#endif //SK_IVER_BACKGROUND_H
