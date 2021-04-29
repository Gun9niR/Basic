#ifndef TOKEN_H
#define TOKEN_H

#include "consts.h"
#include "Value.h"

class Token {
public:
    TokenType type;
    QString lexeme;
    Value value;

public:
    Token(TokenType t, QString l, Value v = Value::NO_VALUE);

    friend QDebug operator<<(QDebug dbg, const Token & token);
};

typedef shared_ptr<Token> TokenPtr;
#endif // TOKEN_H
