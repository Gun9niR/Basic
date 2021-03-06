#include "Scanner.h"
#include "qdebug.h"

Scanner::Scanner():
    source(), start(0), current(0), length(0) {}

shared_ptr<QList<shared_ptr<Token>>> Scanner::getTokens(QString str) {
    shared_ptr<QList<shared_ptr<Token>>> list = make_shared<QList<shared_ptr<Token>>>();
    source = &str;
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

void Scanner::getOneToken(shared_ptr<QList<shared_ptr<Token>>> list) {
    auto c = advance();

    switch (c.unicode()) {
    case '(':
        list->push_back(make_shared<Token>(TokenType::LEFT_PAREN, "("));
        break;
    case ')':
        list->push_back(make_shared<Token>(TokenType::RIGHT_PAREN, ")"));
        break;
    case '+':
        list->push_back(make_shared<Token>(TokenType::PLUS, "+"));
        break;
    case '-':
        list->push_back(make_shared<Token>(TokenType::MINUS, "-"));
        break;
    case '*':
        if (peek().unicode() == '*') {
            ++current;
            list->push_back(make_shared<Token>(TokenType::POWER, "**"));
        } else {
            list->push_back(make_shared<Token>(TokenType::STAR, "*"));
        }
        break;
    case '/':
        list->push_back(make_shared<Token>(TokenType::SLASH, "/"));
        break;
    case '=':
        list->push_back(make_shared<Token>(TokenType::EQUAL, "="));
        break;
    case '<':
        list->push_back(make_shared<Token>(TokenType::LESS, "<"));
        break;
    case '>':
        list->push_back(make_shared<Token>(TokenType::GREATER, ">"));
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

            list->push_back(make_shared<Token>(TokenType::NUMBER, numString, val));
        } else if (c.isLetter()) {
            QString identifier = getIdentifier().toString();

            if (keywords.count(identifier)) {
                // handle keyword
                TokenType keywordType = keywords.at(identifier);
                if (keywordType == TokenType::REM) {
                    // REM and anything following will be ignored
                    throw DetectREM();
                } else {
                    list->push_back(make_shared<Token>(keywords.at(identifier), identifier));
                }
            } else {
                // handle identifier
                list->push_back(make_shared<Token>(TokenType::IDENTIFIER, identifier));
            }
        } else {
            throw (QString("Unexpected character '") + c + "', ignoring this line");
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
