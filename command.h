#ifndef COMMAND_H
#define COMMAND_H

#include "paddle.h"


class Command {
public:
    virtual void Execute(Paddle &paddle) = 0;
};


class MoveLeftCommand : public Command {
public:
    void Execute(Paddle &paddle) {
        paddle.moveLeft();
    }
};


class MoveRightCommand : public Command {
public:
    void Execute(Paddle &paddle) {
        paddle.moveRight();
    }
};


class DefaultCommand : public Command {
public:
    void Execute(Paddle &paddle) {
        paddle.stayAtPlace();
    }
};


#endif