//
// Created by usernick on 29.01.2022.
//

#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include "State.hpp"


class MenuState : public State {
public:
    MenuState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    enum OptionNames {
        Play,
        Exit,
    };

private:
    sf::Sprite            mBackgroundSprite;
    std::vector<sf::Text> mOptions;
    size_t                mOptionIndex;
};


