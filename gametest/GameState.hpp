#pragma once


#include <gametest/State.hpp>
#include <gametest/World.hpp>
#include <gametest/Player.hpp>


class GameState : public State {
public:
    GameState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    World  mWorld;
    Player mPlayer;
};
