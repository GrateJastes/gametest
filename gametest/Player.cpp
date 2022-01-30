#include <iostream>
#include <gametest/Player.hpp>
#include <gametest/Category.hpp>

struct AircraftMover {
    AircraftMover(float vx, float vy): velocity(vx, vy) {}

    void operator()(Aircraft &aircraft, sf::Time dt) const {
        aircraft.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

Player::Player() {
    mKeyBinding[sf::Keyboard::A] = Player::Action::MoveLeft;
    mKeyBinding[sf::Keyboard::D] = Player::Action::MoveRight;
    mKeyBinding[sf::Keyboard::W] = Player::Action::MoveUp;
    mKeyBinding[sf::Keyboard::S] = Player::Action::MoveDown;

    initializeActions();

    std::for_each(
            mActionBinding.begin(), mActionBinding.end(), [&](auto &item) {
                item.second.category = Category::PlayerAircraft;
            }
    );
}

void Player::handleRealtimeInput(CommandQueue &commands) {
    int       i = 0;
    for (auto pair: mKeyBinding) {
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second)) {
            commands.push(mActionBinding[pair.second]);
        }
    }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
    if (event.type == sf::Event::KeyPressed) {
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second)) {
            commands.push(mActionBinding[found->second]);
        }
    }
}

void Player::assignKey(Player::Action action, sf::Keyboard::Key key) {
    mKeyBinding.erase(key);
    mKeyBinding.insert(std::make_pair(key, action));
}

sf::Keyboard::Key Player::getAssignedKey(Player::Action action) const {
    auto found = std::find_if(
            mKeyBinding.begin(), mKeyBinding.end(), [&](const auto &item) {
                return item.second == action;
            }
    );

    return found == mKeyBinding.end() ? sf::Keyboard::Unknown : found->first;
}

bool Player::isRealtimeAction(Player::Action action) {
    switch (action) {
        case Action::MoveDown:
        case Action::MoveUp:
        case Action::MoveLeft:
        case Action::MoveRight:
            return true;
        default:
            return false;
    }
}

void Player::initializeActions() {
    const float player_speed = 200.f;

    mActionBinding[Player::Action::MoveLeft].action  =
            derivedAction<Aircraft>(AircraftMover(-player_speed, 0.f));
    mActionBinding[Player::Action::MoveRight].action =
            derivedAction<Aircraft>(AircraftMover(player_speed, 0.f));
    mActionBinding[Player::Action::MoveUp].action    =
            derivedAction<Aircraft>(AircraftMover(0.f, -player_speed));
    mActionBinding[Player::Action::MoveDown].action  =
            derivedAction<Aircraft>(AircraftMover(0.f, player_speed));
}
