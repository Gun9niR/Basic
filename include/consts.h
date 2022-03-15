#ifndef CONSTS_H
#define CONSTS_H

#include <unordered_map>
#include <map>
#include <memory>
#include <cmath>
#include <vector>
#include "QFile"
#include "QApplication"
#include "QColor"
#include "QTextEdit"
#include "QTextCursor"
#include "QDebug"
#include "QEventLoop"
#include "QString"
#include "QList"
#include "QVariant"
#include "QFileDialog"
#include "QMessageBox"
#include <QMainWindow>

using std::vector;
using std::sort;
using std::map;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

enum CommandType {
    RUN, LOAD, CLEAR, SAVE, DEBUG, HELP, QUIT, LIST
};

enum TokenType {
    // single-character token
    LEFT_PAREN, RIGHT_PAREN, PLUS, MINUS, STAR, SLASH,
    EQUAL, LESS, GREATER, COMMA,

    // two-character token
    POWER,

    // literal
    IDENTIFIER, NUMBER, STRING,

    // keyword
    REM, LET, PRINT, INPUT, GOTO, IF, THEN, END, PRINTF, INPUTS,

    // comment
    COMMENT,

    // error
    ERROR
};

enum ValueType {
    INT, STR, NONE
};

// line number of code
typedef unsigned long LineNum;
// line number of text browser
typedef unsigned long TextLineNum;
// timestamp of varibale
typedef unsigned long TimeStamp;

extern const QString PRINTF_PLACEHOLDER;
extern const QString SPACE;
extern const QString HELP_MESSAGE;

extern const QColor RED;
extern const QColor GREEN;

extern const unordered_map<QString, CommandType> COMMANDS;
#endif // CONSTS_H
