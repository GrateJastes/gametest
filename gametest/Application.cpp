#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cmath>
#include <gametest/Application.hpp>

#include <gametest/ResourceHolder.hpp>
#include <gametest/Command.hpp>
#include <gametest/Fonts.hpp>
#include "GameState.hpp"


Application::Application()
        : mWindow(sf::VideoMode(640, 480), "Test", sf::Style::Close)
          , mWorld(mWindow)
          , mTextures()
          , mFonts()
          , mStatisticsText()
          , mStatisticsUpdateTime()
          , mStatisticsFrameNum(0)
          , mPlayer()
          , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer)) {
    mWindow.setKeyRepeatEnabled(false);

    mFonts.load(Fonts::ID::Main, "assets/fonts/Sansation.ttf");
    mStatisticsText.setFont(mFonts.get(Fonts::ID::Main));
    mStatisticsText.setFillColor(sf::Color::Black);

    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);

    registerStates();
    mStateStack.pushState(States::Title);
}

void Application::run() {
    sf::Clock clock;
    sf::Time  time_since_last_update = sf::Time::Zero;
    while (mWindow.isOpen()) {
        auto cycle_elapsed_time = clock.restart();
        time_since_last_update += cycle_elapsed_time;

        while (time_since_last_update > TIME_PER_FRAME) {
            time_since_last_update -= TIME_PER_FRAME;

            processInput();
            update(TIME_PER_FRAME);

            if (mStateStack.isEmpty()) {
                mWindow.close();
            }
        }

        updateStatistic(cycle_elapsed_time);
        render();
    }
}

void Application::processInput() {
    sf::Event event{};
    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }
}

void Application::render() {
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Application::update(sf::Time dt) {
    mStateStack.update(dt);
}

void Application::updateStatistic(sf::Time elapsed_time) {
    mStatisticsUpdateTime += elapsed_time;
    mStatisticsFrameNum += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.f)) {
        mStatisticsText.setString(
                "FPS: " + std::to_string(mStatisticsFrameNum) + "\n" +
                "Time to update: " +
                std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsFrameNum) + "us"
        );

        mStatisticsUpdateTime -= sf::seconds(1.f);
        mStatisticsFrameNum = 0;
    }
}

void Application::registerStates() {
    mStateStack.registerState<GameState>(States::Game);
//    mStateStack.registerState<TitleState>(States::Title);
//    mStateStack.registerState<TitleState>(States::Title);
//    mStateStack.registerState<TitleState>(States::Title);
}
