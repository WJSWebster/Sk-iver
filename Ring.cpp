//
// Created by William Webster on 15/11/2017.
//

#include "Ring.h"

Ring::Ring(int x, int y, double size) : x(x), y(y), size(size) {}

int Ring::getX() const {
    return x;
}

void Ring::setX(int x) {
    Ring::x = x;
}

int Ring::getY() const {
    return y;
}

void Ring::setY(int y) {
    Ring::y = y;
}

double Ring::getSize() const {
    return size;
}

void Ring::setSize(double size) {
    Ring::size = size;
}
