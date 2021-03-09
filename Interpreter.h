#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "consts.h"
#include "Token.h"
#include "Environment.h"
#include "Stmt.h"
#include "QThread"

class Interpreter: public QThread {

private:
    Environment environment;
    map<int, StmtPtr>& stmts;
    map<int, StmtPtr>::iterator pc;

public:
    Interpreter(map<int, StmtPtr>&);

    void interpret();
};
#endif // INTERPRETER_H
