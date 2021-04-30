#ifndef BASIC_H
#define BASIC_H

#include "consts.h"
#include "util.h"
#include "Stmt.h"
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include "MainWindow.h"

class Basic {
private:
    // code as string, tokens and statements
    map<LineNum, QString> rawInstruction;
    map<LineNum, QString> rawString;

    // state
    QFile file;
    bool isLoadingFile;

    unique_ptr<Interpreter> interpreter;
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

    // start debugging mode
    void startDebug();

    // finish debugging mode, called by mainwindow
    void finishDebug();

    // interpret all code
    void interpretAll();

    // interpret one line, called only in debugging mode, when the interpreter is not null
    void debugStep();

    // interpret the rest of the code, called only in debugging mode
    void interpretRest();

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
};

#endif // BASIC_H
