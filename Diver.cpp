//
// Created by William Webster on 15/11/2017.
//

#include "Diver.h"

Diver::Diver(int x, int y, int size) : x(x), y(y), size(size) {}

int Diver::getX() const {
    return x;
}

void Diver::setX(int x) {
    Diver::x = x;
}

int Diver::getY() const {
    return y;
}

void Diver::setY(int y) {
    Diver::y = y;
}

int Diver::getSize() const {
    return size;
}

void Diver::setSize(int size) {
    Diver::size = size;
}
