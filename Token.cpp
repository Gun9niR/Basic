#include "Token.h"

Token::Token(TokenType t,
             QString l,
             int v): type(t), lexeme(l), value(v) { }

QDebug operator<<(QDebug dbg, const Token & token) {
    QString typeName;
    switch(token.type) {
        case LEFT_PAREN:
            typeName = "RIGHT_PAREN";
            break;
        case RIGHT_PAREN:
            typeName = "RIGHT_PAREN";
            break;
        case PLUS:
            typeName = "PLUS";
            break;
        case MINUS:
            typeName = "MINUS";
            break;
        case STAR:
            typeName = "STAR";
            break;
        case SLASH:
            typeName = "SLASH";
            break;
        case EQUAL:
            typeName = "EQUAL";
            break;
        case LESS:
            typeName = "LESS";
            break;
        case GREATER:
            typeName = "GREATER";
            break;
        case POWER:
            typeName = "POWER";
            break;
        case IDENTIFIER:
            typeName = "IDENTIFIER";
            break;
        case NUMBER:
            typeName = "NUMBER";
            break;
        case REM:
            typeName = "REM";
            break;
        case LET:
            typeName = "LET";
            break;
        case PRINT:
            typeName = "PRINT";
            break;
        case INPUT:
            typeName = "INPUT";
            break;
        case GOTO:
            typeName = "GOTO";
            break;
        case IF:
            typeName = "IF";
            break;
        case THEN:
            typeName = "THEN";
            break;
        case END:
            typeName = "END";
            break;
        case COMMENT:
            typeName = "COMMENT";
            break;
    }
    QString msg = "Type name: " + typeName + ", Lexeme: " + token.lexeme;
    if (token.type == TokenType::NUMBER) {
        msg += ", Value: " + QString::number(token.value);
    }
    dbg << msg;
    return dbg;
}
