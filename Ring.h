//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_RING_H
#define SK_IVER_RING_H

class Ring
{
    int x = 0;
    int y = 0;
    double size = 0;

public:
    Ring(int x, int y, double size);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    double getSize() const;

    void setSize(double size);
};

#endif //SK_IVER_RING_H
