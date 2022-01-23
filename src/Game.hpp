#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceHolder.hpp"
#include "Textures.hpp"

#define PLAYER_SPEED 200.f;
#define TIME_PER_FRAME sf::seconds(1.f / 60.f)

struct Direction {
    bool up;
    bool down;
    bool left;
    bool right;

    Direction() {
        up = down = left = right = false;
    }
};

class Game {
public:
    Game();

    void run();

private:
    sf::RenderWindow mWindow;
    sf::Sprite mPlayer;
    ResourceHolder<sf::Texture, Textures::ID> mTextures;
    Direction mDirection;

    void processEvents();
    void update(sf::Time dt);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool is_pressed);
};
