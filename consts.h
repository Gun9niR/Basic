#ifndef CONSTS_H
#define CONSTS_H

#include <unordered_map>
#include <map>
#include <memory>
#include "QString"
#include "QList"
#include <cmath>
#include <vector>
#include "qfile.h"
#include "QApplication"

using std::vector;
using std::map;
using std::unordered_map;
using std::shared_ptr;
using std::make_shared;

enum CommandType {
    RUN, LOAD, CLEAR, HELP, QUIT
};

enum TokenType {
    // single-character token
    LEFT_PAREN, RIGHT_PAREN, PLUS, MINUS, STAR, SLASH,
    EQUAL, LESS, GREATER,

    // two-character token
    POWER,

    // literal
    IDENTIFIER, NUMBER,

    // keyword
    REM, LET, PRINT, INPUT, GOTO, IF, THEN, END
};

#endif // CONSTS_H
