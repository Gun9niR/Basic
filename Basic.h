#ifndef BASIC_H
#define BASIC_H

#include "consts.h"
#include "Stmt.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"

class Basic {
private:
    const std::unordered_map<QString, CommandType> COMMANDS {
        { "RUN", CommandType::RUN },
        { "LOAD", CommandType::LOAD },
        { "CLEAR", CommandType::CLEAR },
        { "HELP", CommandType::HELP },
        { "QUIT", CommandType::QUIT },
        { "LIST", CommandType::LIST },
    };

    // code as string, tokens and statements
    map<LineNum, QString> rawInstruction;
    map<LineNum, QString> rawString;

    // state
    QFile file;
    bool isLoadingFile;

    shared_ptr<Interpreter> interpreter;
    Environment environment;

    Basic();
    ~Basic();
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

    // run the command
    void runCommand(CommandType type);

    // clear environment, only invoked when running clear command
    void clearEnvironment();

private:
    // get line number from a instruction string
    LineNum getLineNumber(QString& str);

    // display code with line number alignment
    void displayInstruction();

    // display original text
    void displayCode();

    // check if a string is a command
    bool matchCommand(QString& str);

    // check if a string match those three stmts
    bool matchStmtWithoutLineNumber(QString& str, QString& stmt);

    // helper function, get the number of digits of an integer
    int getDigits(int x);
};

#endif // BASIC_H
