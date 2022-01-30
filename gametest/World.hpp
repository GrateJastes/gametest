#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <gametest/ResourceHolder.hpp>
#include <gametest/SceneNode.hpp>
#include <gametest/Aircraft.hpp>
#include <gametest/CommandQueue.hpp>

class World : private sf::NonCopyable {
public:
    explicit World(sf::RenderWindow &window);

    void update(sf::Time dt);

    void draw();

    CommandQueue &getCommandQueue();

private:
    void loadTextures();

    void buildScene();

    void adaptPlayerPosition();

private:
    enum {
        BACKGROUND,
        AIR,
        LAYER_COUNT,
    };

private:
    sf::RenderWindow                     &mWindow;
    sf::View                             mWorldView;
    TextureHolder                        mTextures;
    SceneNode                            mSceneGraph;
    std::array<SceneNode *, LAYER_COUNT> mSceneLayers;

    sf::FloatRect mWorldBounds;
    sf::Vector2f  mSpawnPosition;
    float         mScrollSpeed;
    Aircraft      *mPlayerAircraft;

    CommandQueue mCommandQueue;

    void adaptPlayerVelocity();
};


