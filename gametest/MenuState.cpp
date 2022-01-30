//
// Created by usernick on 29.01.2022.
//

#include <SFML/Graphics/Text.hpp>
#include "MenuState.hpp"
#include "Utility.hpp"


MenuState::MenuState(StateStack &stack, State::Context context):
        State(stack, context)
        , mBackgroundSprite()
        , mOptionIndex(0)
        , mOptions() {
    auto texture = context.textures->get(Textures::ID::TitleScreen);
    auto font    = context.fonts->get(Fonts::ID::Main);

    mBackgroundSprite.setTexture(texture);

    sf::Text play_option;

    play_option.setFont(font);
    play_option.setString("Play");
    centerOrigin(play_option);
    play_option.setPosition(context.window->getView().getSize() / 2.f);
    mOptions.push_back(play_option);

    sf::Text exit_option;

    exit_option.setFont(font);
    exit_option.setString("Exit");
    centerOrigin(exit_option);
    exit_option.setPosition(play_option.getPosition() + sf::Vector2f(0.f, 30.f));
    mOptions.push_back(exit_option);
//    updateOptionText();
}

void MenuState::draw() {

}

bool MenuState::update(sf::Time dt) {
    return false;
}

bool MenuState::handleEvent(const sf::Event &event) {
    return false;
}
