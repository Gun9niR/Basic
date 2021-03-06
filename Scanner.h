#ifndef SCANNER_H
#define SCANNER_H
#include <map>
#include <unordered_map>
#include "Token.h"
#include <memory>
#include "qlist.h"

using std::shared_ptr;
using std::make_shared;
using std::unordered_map;
using std::map;

class Scanner {
private:
    // exceptions
    class DetectREM {};

private:
    const unordered_map<QString, TokenType> keywords {
        {"REM", TokenType::REM},
        {"LET", TokenType::LET},
        {"PRINT", TokenType::PRINT},
        {"INPUT", TokenType::INPUT},
        {"GOTO", TokenType::GOTO},
        {"IF", TokenType::IF},
        {"THEN", TokenType::THEN},
        {"END", TokenType::END},
    };

    // string being scanned
    QStringRef source;

    // pointers to source
    int start;
    int current;

    // length of the string being scanned
    int length;

private:
    void getOneToken(shared_ptr<QList<TokenPtr>> list);

    bool isAtEnd();

    QChar advance();

    QChar peek();

    QStringRef getNumber();

    QStringRef getIdentifier();

public:
    Scanner();

    shared_ptr<QList<TokenPtr>> getTokens(QString str);
};

#endif // SCANNER_H
