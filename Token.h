#ifndef TOKEN_H
#define TOKEN_H

#include "consts.h"
#include "QDebug"

class Token {
public:
    TokenType type;
    QString lexeme;
    double value;

public:
    Token(TokenType t, QString l, double v = std::numeric_limits<double>::quiet_NaN());

    friend QDebug operator<<(QDebug dbg, const Token & token);
};

typedef shared_ptr<Token> TokenPtr;
#endif // TOKEN_H
