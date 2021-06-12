#include <iostream>
#include "../include/header.h"

int main()
{
    std::srand(std::time(nullptr));

    Player* player = new Player;

    player->fillTracks();

    player->control();

    delete player;
}