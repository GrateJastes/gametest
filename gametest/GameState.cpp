//
// Created by usernick on 29.01.2022.
//

#include <gametest/GameState.hpp>


void GameState::draw() {
    mWorld.draw();
}

bool GameState::update(sf::Time dt) {
    mWorld.update(dt);

    CommandQueue &commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    return true;
}


bool GameState::handleEvent(const sf::Event &event) {
    CommandQueue &commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

//    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//        requestStackPush(States::Pause);

    return true;
}

GameState::GameState(StateStack &stack, State::Context context):
        State(stack, context)
        , mWorld(*context.window)
        , mPlayer(*context.player) {}
