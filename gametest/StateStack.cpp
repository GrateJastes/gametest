//
// Created by usernick on 29.01.2022.
//

#include <gametest/StateStack.hpp>
#include <cassert>


StatePtr StateStack::createState(States::ID state_id) {
    auto found = mFactories.find(state_id);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::handleEvent(const sf::Event &event) {
    for (auto iterator = mStack.rbegin(); iterator != mStack.rend(); ++iterator) {
        if (!(*iterator)->handleEvent(event)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time dt) {
    for (auto iterator = mStack.rbegin(); iterator != mStack.rend(); ++iterator) {
        if (!(*iterator)->update(dt)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::draw() {
    for (auto &item: mStack) {
        item->draw();
    }
}

void StateStack::applyPendingChanges() {
    for (auto &change: mPendingList) {
        switch (change.action) {
            case Action::Push:
                mStack.push_back(createState(change.stateID));
                break;
            case Action::Pop:
                mStack.pop_back();
                break;
            case Action::Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

bool StateStack::isEmpty() const {
    return mStack.empty();
}

StateStack::StateStack(State::Context context):
        mStack()
        , mPendingList()
        , mContext(context)
        , mFactories() {}

void StateStack::clearStates() {
    mPendingList.push_back(PendingChange(Action::Clear));
}

void StateStack::pushState(States::ID state_id) {
    mPendingList.push_back(PendingChange(Action::Push, state_id));
}

void StateStack::popState() {
    mPendingList.push_back(PendingChange(Action::Pop));
}

StateStack::PendingChange::PendingChange(StateStack::Action action, States::ID id)
        : action(action)
          , stateID(id) {}
