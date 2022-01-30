#include <SFML/Graphics.hpp>
#include <iostream>

#include <gametest/Application.hpp>


int main() {
    try {
        Application game;
        game.run();
    } catch (std::exception &e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}