#ifndef STMT_H
#define STMT_H

#include "Environment.h"
#include "Token.h"
#include "Expr.h"

class Stmt {
public:
    virtual void execute(Environment &) = 0;
};

typedef shared_ptr<Stmt> StmtPtr;

class LetStmt: public Stmt {
private:
    TokenPtr name;
    ExprPtr initializer;

public:
    void execute(Environment &) override;
};

class PrintStmt: public Stmt {
private:
    ExprPtr expr;

public:
    void execute(Environment &) override;
};

class InputStmt: public Stmt {
private:
    TokenPtr name;

public:
    void execute(Environment &) override;
};

class GotoStmt: public Stmt {
private:
    int lineNum;

public:
    void execute(Environment &) override;
};

class IfStmt: public Stmt {
private:
    TokenPtr op;
    ExprPtr expr1;
    ExprPtr expr2;
    int lineNum;

public:
    void execute(Environment &) override;
};

class EndStmt: public Stmt {
public:
    void execute(Environment &) override;
};

#endif // STMT_H
