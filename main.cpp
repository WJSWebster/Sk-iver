//
// Created by William Webster on 15/11/2017.
//

#include "Game.h"


Game *game = nullptr;

int main()
{
    game = new Game;

    game->setUp();
    game->update();

    return 0;
}
