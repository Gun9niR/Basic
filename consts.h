#ifndef CONSTS_H
#define CONSTS_H

#include <unordered_map>
#include "qstring.h"

enum CommandType {
    RUN, LOAD, CLEAR, HELP, QUIT
};


enum ExprType {
    ADD, SUB, MULT, DIV, POW
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
