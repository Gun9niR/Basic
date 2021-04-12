#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "consts.h"
#include "Token.h"
#include "Environment.h"
#include "Stmt.h"
#include "QThread"
#include "Scanner.h"
#include "Parser.h"

class Interpreter {
private:
    map<LineNum, QString>& rawInstructions;
    map<LineNum, StmtPtr> stmts;

    map<LineNum, StmtPtr>::iterator pc;
    Scanner scanner;
    Parser parser;
    Environment& environment;

public:
    Interpreter(map<LineNum, QString>&, Environment&);

    void interpret();

    static void interpret(QString&, Environment&);
};
#endif // INTERPRETER_H
