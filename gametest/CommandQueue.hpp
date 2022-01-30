#pragma once

#include <queue>
#include <gametest/Command.hpp>

class CommandQueue {
public:
    void push(const Command &command);

    Command pop();

    bool isEmpty() const;

//private:
    std::queue<Command> mQueue;
};
