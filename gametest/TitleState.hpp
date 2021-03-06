//
// Created by usernick on 29.01.2022.
//

#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"


class TitleState : public State {
    TitleState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    sf::Sprite mBackgroundSprite;
    sf::Text   mText;

    bool     mShowText;
    sf::Time mTextEffectTime;
};


