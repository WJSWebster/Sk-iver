//
// Created by William Webster on 15/11/2017.
//

#ifndef SK_IVER_DIVER_H
#define SK_IVER_DIVER_H


class Diver {
    int x = 0;
    int y = 0;
    int size = 20;

public:
    Diver(int x, int y, int size);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getSize() const;

    void setSize(int size);

private: // should be a singleton?
};

#endif //SK_IVER_DIVER_H
