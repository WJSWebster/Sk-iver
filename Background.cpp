//
// Created by William Webster on 06/12/2017.
//

#include <SFML/Graphics.hpp>
#include "Background.h"

using namespace std;

Background::Background() {
    setImage("skydiving_placeholder.jpg");
    setSprite();
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
