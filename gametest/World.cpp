#include <SFML/Graphics/Texture.hpp>
#include <valarray>
#include <iostream>

#include <gametest/World.hpp>
#include <gametest/SpriteNode.hpp>

World::World(sf::RenderWindow &window)
        : mWindow(window)
          , mWorldView(window.getDefaultView())
          , mSceneLayers()
          , mWorldBounds(
                0.f,
                0.f,
                mWorldView.getSize().x,
                5000.f
        )
          , mSpawnPosition(
                mWorldView.getSize().x / 2.f,
                mWorldBounds.height - mWorldView.getSize().y / 2.f
        )
          , mScrollSpeed(-50.f)
          , mPlayerAircraft(nullptr)
          , mCommandQueue() {
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures() {
    mTextures.load(Textures::ID::EAGLE, "assets/textures/Eagle.png");
    mTextures.load(Textures::ID::RAPTOR, "assets/textures/Raptor.png");
    mTextures.load(Textures::ID::DESERT, "assets/textures/Desert.png");
}

void World::buildScene() {
    for (size_t i = 0; i < LAYER_COUNT; ++i) {
        auto layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture &texture = mTextures.get(Textures::ID::DESERT);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    auto backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[BACKGROUND]->attachChild(std::move(backgroundSprite));

    auto leader = std::make_unique<Aircraft>(Aircraft::Type::EAGLE, mTextures);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mSceneLayers[AIR]->attachChild(std::move(leader));
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
    mPlayerAircraft->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }

    adaptPlayerVelocity();
    mSceneGraph.update(dt);
    adaptPlayerPosition();
}

CommandQueue &World::getCommandQueue() {
    return mCommandQueue;
}

void World::adaptPlayerPosition() {
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    const float   borderDistance = 50.f;

    auto position = mPlayerAircraft->getPosition();

    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);

    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

    mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity() {
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f) {
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
    }

    mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}
