#pragma once
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class Keyboard {
public:
    Keyboard() {
        tcgetattr(STDIN_FILENO, &old_);
        termios raw = old_;
        raw.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    }

    ~Keyboard() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_);
    }

    bool poll(char& c) {
        return read(STDIN_FILENO, &c, 1) > 0;
    }

private:
    termios old_;
};