#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include <QList>
#include "qfile.h"
#include "Scanner.h"
#include "consts.h"
#include "Token.h"
#include <memory>
#include "Parser.h"
#include "Environment.h"

using std::shared_ptr;
using std::map;
using std::make_shared;

class Interpreter: public QObject {
    Q_OBJECT

private:
    const std::unordered_map<QString, CommandType> COMMANDS {
        { "RUN", CommandType::RUN },
        { "LOAD", CommandType::LOAD },
        { "CLEAR", CommandType::CLEAR },
        { "HELP", CommandType::HELP },
        { "QUIT", CommandType::QUIT },
    };

    // stores the opened file
    QFile file;

    // stores code as string
    map<int, QString> rawInstruction;

    // stores tokens
    map<int, shared_ptr<QList<shared_ptr<Token>>>> tokens;

    // stores statements
    map<int, shared_ptr<Stmt>> stmts;

    // environment
    Environment environment;

    // tokenizer
    Scanner scanner;

    // parser
    Parser parser;

signals:
    void codeAppendRow(QString str);

    void clickClearButton();

    void clearDisplays();

public:
    Interpreter();

    // load code from a file
    void loadFile(QString fileName);

    // reset all properties
    void reset();

    // insert raw instruction from console or file
    void handleRawInstruction(QString& str);

    void interpret();

    // debug functions
    void showTokens();

private:
    // get line number from a instruction string
    int getLineNumber(QString& str);

    // display code in codeAppendRow in the text browser
    void displayCode();

    // check if a string is a command
    bool matchCommand(QString& str);

    // run the command
    void runCommand(CommandType type);
};
#endif // INTERPRETER_H
