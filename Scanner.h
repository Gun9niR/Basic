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

    map<int, QString>& rawInstruction;
    map<int, shared_ptr<QList<Token>>>& tokens;

    // string being scanned
    QStringRef source;

    // pointers to char
    int start;
    int current;

    // length of the string being scanned
    int length;
private:
    shared_ptr<QList<Token>> getLineToken();

    void getOneToken(shared_ptr<QList<Token>> list);

    // helper function
    bool isAtEnd();
    QChar advance();
    QChar peek();
    QStringRef getNumber();
    QStringRef getIdentifier();

public:
    Scanner(map<int, QString>& i, map<int, shared_ptr<QList<Token>>>& t);

    void getTokens();
};

#endif // SCANNER_H
