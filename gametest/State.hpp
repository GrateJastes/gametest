//
// Created by usernick on 29.01.2022.
//

#pragma once

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <gametest/StateIdentifiers.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <gametest/ResourceHolder.hpp>


class State;
class StateStack;
class Player;


typedef std::unique_ptr<State> StatePtr;


class State {
public:
    struct Context {
        Context(
                sf::RenderWindow &window,
                TextureHolder &textures,
                FontHolder &fonts,
                Player &player);

        sf::RenderWindow *window;
        TextureHolder    *textures;
        FontHolder       *fonts;
        Player           *player;
    };

public:
    State(StateStack &stack, Context context);

    virtual ~State() = default;

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event &event) = 0;

protected:
    void requestStackPush(States::ID state_id);
    void requestStackPop();
    void requestStackClear();

    Context getContext() const;

private:
    StateStack *mStack;
    Context    mContext;
};


