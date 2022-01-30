//
// Created by usernick on 29.01.2022.
//

#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <map>
#include <gametest/State.hpp>


class StateStack : private sf::NonCopyable {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(State::Context context);

    template<typename T>
    void registerState(States::ID state_id);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event &event);

    void pushState(States::ID state_id);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    StatePtr createState(States::ID state_id);
    void applyPendingChanges();

private:
    struct PendingChange {
        explicit PendingChange(Action action, States::ID id = States::ID::None);

        Action     action;
        States::ID stateID;
    };

private:
    std::vector<StatePtr>      mStack;
    std::vector<PendingChange> mPendingList;

    State::Context                                  mContext;
    std::map<States::ID, std::function<StatePtr()>> mFactories;
};

template<typename T>
void StateStack::registerState(States::ID state_id) {
    mFactories[state_id] = [this]() {
        return std::make_unique<T>(*this, mContext); // TODO: idk
    };
}
