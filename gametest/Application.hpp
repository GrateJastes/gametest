#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <gametest/ResourceHolder.hpp>
#include <gametest/Textures.hpp>
#include <gametest/World.hpp>
#include <gametest/Player.hpp>
#include <gametest/StateStack.hpp>


#define TIME_PER_FRAME sf::seconds(1.f / 60.f)

class Application {
public:
    Application();

    void run();

private:
    void processInput();
    void update(sf::Time dt);
    void render();

    void updateStatistic(sf::Time elapsed_time);

    void registerStates();

private:
    sf::RenderWindow mWindow;
    World            mWorld;

    TextureHolder mTextures;
    FontHolder    mFonts;
    Player        mPlayer;

    StateStack mStateStack;

    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    size_t   mStatisticsFrameNum;
};
