#include <SFML/Graphics.hpp>
#include <iostream>

#include "Game.hpp"

int main()
{
    try {
        Game game;
        game.run();
    } catch (std::exception &e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}