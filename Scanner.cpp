#include "Scanner.h"
#include "qdebug.h"

Scanner::Scanner(map<int, QString>& i, map<int, shared_ptr<QList<Token>>>& t):
    rawInstruction(i), tokens(t),
    source(), length(0), start(0), current(0) {}

void Scanner::getTokens() {
    // iterate through each line of string
    for (auto i = rawInstruction.begin(); i != rawInstruction.end(); ++i) {
        int lineNum = i->first;
        source = &i->second;

        try {
            // a tokenList stores the token from one line of string
            auto tokenList = getLineToken();

            // put the pointer to the list into the tokens map
            tokens[lineNum] = tokenList;
        } catch (QString errMsg) {
            throw QString(QString::number(lineNum) + ": " + errMsg);
        }
    }
}

shared_ptr<QList<Token>> Scanner::getLineToken() {
    shared_ptr<QList<Token>> list = make_shared<QList<Token>>();

    start = 0;
    current = 0;
    length = source.length();

    while (!isAtEnd()) {
        start = current;
        try {
            getOneToken(list);
        } catch (DetectREM) {
            break;
        }
    }
    return list;
}

void Scanner::getOneToken(shared_ptr<QList<Token>> list) {
    auto c = advance();

    switch (c.unicode()) {
    case '(':
        list->push_back(Token(TokenType::LEFT_PAREN, "("));
        break;
    case ')':
        list->push_back(Token(TokenType::RIGHT_PAREN, ")"));
        break;
    case '+':
        list->push_back(Token(TokenType::PLUS, "+"));
        break;
    case '-':
        list->push_back(Token(TokenType::MINUS, "-"));
        break;
    case '*':
        if (peek().unicode() == '*') {
            ++current;
            list->push_back(Token(TokenType::POWER, "**"));
        } else {
            list->push_back(Token(TokenType::STAR, "*"));
        }
        break;
    case '/':
        list->push_back(Token(TokenType::SLASH, "/"));
        break;
    case '=':
        list->push_back(Token(TokenType::EQUAL, "="));
        break;
    case '<':
        list->push_back(Token(TokenType::LESS, "<"));
        break;
    case '>':
        list->push_back(Token(TokenType::GREATER, ">"));
        break;
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        break;
    default: // handle numbers, keywords and identifiers
        if (c.isDigit()) {
            // handle number
            QString numString = getNumber().toString();
            double val = numString.toDouble();

            list->push_back(Token(TokenType::NUMBER, numString, val));
        } else if (c.isLetter()) {
            QString identifier = getIdentifier().toString();

            if (keywords.count(identifier)) {
                // handle keyword
                TokenType keywordType = keywords.at(identifier);
                if (keywordType == TokenType::REM) {
                    // REM and anything following will be ignored
                    throw DetectREM();
                } else {
                    list->push_back(Token(keywords.at(identifier), identifier));
                }
            } else {
                // handle identifier
                list->push_back(Token(TokenType::IDENTIFIER, identifier));
            }
        } else {
            throw (QString("Unexpected character '") + c + "'");
        }
        break;
    }
}

bool Scanner::isAtEnd() {
    return current >= length;
}

QChar Scanner::advance() {
    ++current;
    return source[current - 1];
}

QChar Scanner::peek() {
    if (isAtEnd()) {
        return 0;
    }
    return source[current];
}

QStringRef Scanner::getNumber() {
    while (peek().isDigit()) {
        ++current;
    }
    return source.mid(start, current - start);
}

QStringRef Scanner::getIdentifier() {
    for (QChar c = peek(); c.isLetterOrNumber() || c == '_'; c = peek()) {
        ++current;
    }
    return source.mid(start, current - start);
}
