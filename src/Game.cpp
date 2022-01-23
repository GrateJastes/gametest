#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cmath>
#include "Game.hpp"

#include "ResourceHolder.hpp"

Game::Game()
: mWindow(sf::VideoMode(960, 720), "Test")
, mPlayer() {
    mTextures.load(Textures::ID::AIRPLANE, "assets/textures/Airplane.png");

    mPlayer.setTexture(mTextures.get(Textures::ID::AIRPLANE));
    mPlayer.setPosition(100.f, 100.f);
}

void Game::run() {
    sf::Clock clock;
    sf::Time time_since_last_update = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();

        time_since_last_update += clock.restart();

        while (time_since_last_update > TIME_PER_FRAME) {
            time_since_last_update -= TIME_PER_FRAME;
            processEvents();
            update(TIME_PER_FRAME);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::update(sf::Time dt) {
    sf::Vector2f movement(0.f, 0.f);

    if (mDirection.up) movement.y -= 1.f;
    if (mDirection.down) movement.y += 1.f;
    if (mDirection.left) movement.x -= 1.f;
    if (mDirection.right) movement.x += 1.f;

    if (movement.x != 0 && movement.y != 0) {
        float mod = sqrtf(powf(movement.x, 2.0f) + powf(movement.y, 2.0f));
        movement /= mod;
    }

    movement *= PLAYER_SPEED;
    mPlayer.move(movement * dt.asSeconds());
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool is_pressed) {
    switch (key) {
        case sf::Keyboard::W:
            mDirection.up = is_pressed;
            break;
        case sf::Keyboard::S:
            mDirection.down = is_pressed;
            break;
        case sf::Keyboard::A:
            mDirection.left = is_pressed;
            break;
        case sf::Keyboard::D:
            mDirection.right = is_pressed;
            break;
        case sf::Keyboard::Escape:
            mWindow.close();
            break;
        default:
            break;
    }
}
