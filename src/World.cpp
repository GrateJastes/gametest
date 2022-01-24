#include <SFML/Graphics/Texture.hpp>

#include "World.hpp"
#include "SpriteNode.hpp"

World::World(sf::RenderWindow &window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mWorldBounds(
        0.f,
        0.f,
        mWorldView.getSize().x,
        2000.f)
, mSpawnPosition(
        mWorldView.getSize().x / 2.f,
        mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mPlayerAircraft(nullptr) {
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures() {
    mTextures.load(Textures::ID::EAGLE, "assets/textures/Airplane.png");
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
    mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[AIR]->attachChild(std::move(leader));

    auto leftEscort = std::make_unique<Aircraft>(Aircraft::Type::RAPTOR, mTextures);
    leftEscort->setPosition(-150.f, 100.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));

    auto rightEscort = std::make_unique<Aircraft>(Aircraft::Type::RAPTOR, mTextures);
    rightEscort->setPosition(150.f, 100.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150) {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
    }

    mSceneGraph.update(dt);
}
