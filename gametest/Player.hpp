#pragma once

#include <SFML/Window/Event.hpp>
#include <gametest/CommandQueue.hpp>
#include <gametest/Aircraft.hpp>

class Player {
public:
    enum class Action {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
    };

    void assignKey(Action action, sf::Keyboard::Key key);

    sf::Keyboard::Key getAssignedKey(Action action) const;

public:
    Player();

    void handleEvent(const sf::Event &event, CommandQueue &commands);

    void handleRealtimeInput(CommandQueue &commands);

private:
    static bool isRealtimeAction(Action action);

    void initializeActions();

private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command>           mActionBinding;
};
