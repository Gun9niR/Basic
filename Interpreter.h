#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "consts.h"
#include "Token.h"
#include "Environment.h"
#include "Stmt.h"
#include "QThread"
#include "Scanner.h"
#include "Parser.h"
#include "util.h"

class Interpreter {
private:
    map<LineNum, QString>& rawInstructions;
    map<LineNum, StmtPtr> stmts;
    map<LineNum, TextLineNum> codeLine2TextLine;

    map<LineNum, StmtPtr>::iterator pc;
    Scanner scanner;
    Parser parser;
    Environment& environment;

    // invoked before entering debug or run mode, scan, parse and highlight the raw instructions
    void processRawInstruction();

    // displaySyntaxTree of all code
    void displaySyntaxTree();

    // highlight code in codeDisplay at given line number (actually, block)
    void addCodeDisplayHighlight(TextLineNum, const QColor&);

    // remove highlight codeDisplay at given line number (actually, block)
    void removeCodeDisplayHighlight(TextLineNum);

    // map code line number to text line number to facilitate highlighting
    void mapCodeLine2TextLine();

    // highlight and display syntax tree for the line of code to be interpreted
    void prepareInterpretOne();

    // start interpreting from current pc to the end
    // return true if program ends successfully
    bool interpretFromCurrentPc();

    // interpret one
    bool interpretOne();

    // remove highlight color of current line pointed to by pc
    void removeCurrentLineColor();

    // set highlight color of current line pointed to by pc
    void setCurrentLineColor(const QColor&);

public:
    Interpreter(map<LineNum, QString>&, Environment&);

    // enter debug mode
    void startDebugging();

    // interpret one line of code in debug mode
    void debugStep();

    // interpret every line of code from start to the end, and display success message on success
    void interpretAll();

    // interpret the rest of the code, invoked during debug mode
    void interpretRest();

    // interpret code entered from console
    static void interpret(const QString&, Environment&);
};
#endif // INTERPRETER_H
