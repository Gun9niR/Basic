#include "Scanner.h"
#include "qdebug.h"

Scanner::Scanner():
    source(), start(0), current(0), length(0) {}

shared_ptr<QList<TokenPtr>> Scanner::getTokens(const QString& str) {
    shared_ptr<QList<TokenPtr>> list = make_shared<QList<TokenPtr>>();
    source = str;
    start = 0;
    current = 0;
    length = source.length();

    while (!isAtEnd()) {
        start = current;
        try {
            getOneToken(list);
        } catch (DetectREM) {
            QString comment = str.mid(current).trimmed();
            list->push_back(make_shared<Token>(TokenType::COMMENT, comment));
            break;
        }
    }
    return list;
}

void Scanner::getOneToken(shared_ptr<QList<TokenPtr>> list) {
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
    case ',':
        list->push_back(make_shared<Token>(TokenType::COMMA, ","));
        break;
    case '\'':
    case '"':
        list->push_back(getString(c.unicode()));
        break;
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        break;
    default: // handle numbers, keywords and identifiers
        if (c.isDigit()) {
            list->push_back(getNumber());
        } else if (c.isLetter() || c == '_') {
            TokenPtr identifierPtr = getIdentifier();
            list->push_back(getIdentifier());
            if (identifierPtr->type == TokenType::REM) {
                throw DetectREM();
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
        return QChar(0);
    }
    return source[current];
}

TokenPtr Scanner::getNumber() {
    while (peek().isDigit()) {
        ++current;
    }
    QString numString = source.mid(start, current - start);
    int val = numString.toInt();
    return make_shared<Token>(TokenType::NUMBER, numString, val);
}

TokenPtr Scanner::getIdentifier() {
    for (QChar c = peek(); c.isLetterOrNumber() || c == '_'; c = peek()) {
        ++current;
    }


    QString identifier = source.mid(start, current - start);

    if (keywords.count(identifier)) {
        // handle keyword
        TokenType keywordType = keywords.at(identifier);
        if (keywordType == TokenType::REM) {
            // REM and anything following will be ignored
            return make_shared<Token>(keywords.at(identifier), identifier);
        } else {
            return make_shared<Token>(keywords.at(identifier), identifier);
        }
    } else {
        // handle identifier
        return make_shared<Token>(TokenType::IDENTIFIER, identifier);
    }
}

TokenPtr Scanner::getString(const QChar& delimiter) {
    QChar notAllowed = (delimiter.unicode() == '"') ? QChar('\'') : QChar('"');
    QChar nextChar;

    while ((nextChar = peek()).isPrint()) {
        if (nextChar == notAllowed) {
            throw QString(QString(nextChar) + " not allowed in a string");
        } else if (nextChar == delimiter) {
            ++current;
            return make_shared<Token>(TokenType::STRING,
                                      source.mid(start, current - start),
                                      source.mid(start + 1, current - start - 2)
                                      );
        }
        ++current;
    }

    throw QString("Expect a " + QString(delimiter) + " at end the string");
}
