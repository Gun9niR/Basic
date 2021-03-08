#ifndef BASIC_H
#define BASIC_H

#include "consts.h"
#include "Stmt.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

class Basic: public QObject {
    Q_OBJECT

private:
    const std::unordered_map<QString, CommandType> COMMANDS {
        { "RUN", CommandType::RUN },
        { "LOAD", CommandType::LOAD },
        { "CLEAR", CommandType::CLEAR },
        { "HELP", CommandType::HELP },
        { "QUIT", CommandType::QUIT },
    };

    // code as string, tokens and statements
    map<int, QString> rawInstruction;
    map<int, shared_ptr<QList<TokenPtr>>> tokens;
    map<int, StmtPtr> stmts;

    // state
    QFile file;

    // tools
    shared_ptr<Interpreter> interpreter;
    Scanner scanner;
    Parser parser;

    Basic();
    ~Basic();

signals:
    void codeAppendRow(QString str);

    void clickClearButton();

    void clearDisplays();

public:
    // singleton pattern
    static Basic& getInstance();

    // load code from a file
    void loadFile(QString fileName);

    // reset all properties
    void reset();

    // insert raw instruction from console or file
    void handleRawInstruction(QString& str);

    // instantiate interpreter and interpret
    void interpret();

    // debug functions
    void showTokens();

private:
    // get line number from a instruction string
    int getLineNumber(QString& str);

    // display code and syntax tree
    void display();

    // display code with codeAppendRow in the text browser
    void displayCode();

    // display syxtax tree with codeAppendRow in the text browser
    void displaySyntaxTree();

    // check if a string is a command
    bool matchCommand(QString& str);

    // run the command
    void runCommand(CommandType type);

    int getDigits(int x);
};

#endif // BASIC_H
