//
// Created by usernick on 29.01.2022.
//

#include <gametest/State.hpp>
#include <gametest/StateStack.hpp>


State::Context::Context(
        sf::RenderWindow &window,
        TextureHolder &textures,
        FontHolder &fonts,
        Player &player)
        : window(&window)
          , textures(&textures)
          , fonts(&fonts)
          , player(&player) {

}

State::State(StateStack &stack, State::Context context):
        mStack(&stack)
        , mContext(context) {}

void State::requestStackPush(States::ID state_id) {
    mStack->pushState(state_id);
}

void State::requestStackPop() {
    mStack->popState();
}

void State::requestStackClear() {
    mStack->clearStates();
}

State::Context State::getContext() const {
    return mContext;
}
