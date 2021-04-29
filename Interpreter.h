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
    map<LineNum, QColor> highlights;

    map<LineNum, StmtPtr>::iterator pc;
    Scanner scanner;
    Parser parser;
    Environment& environment;

    // invoked before entering debug or run mode, scan, parse and highlight the raw instructions
    void processRawInstruction();

    // highlight code in codeDisplay with <highlights> map
    void setCodeDisplayHighlight();
public:
    Interpreter(map<LineNum, QString>&, Environment&);

    void interpret();

    static void interpret(QString&, Environment&);
};
#endif // INTERPRETER_H
