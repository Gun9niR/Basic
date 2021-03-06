#ifndef STMT_H
#define STMT_H

#include "Environment.h"
#include "Token.h"
#include "Expr.h"

class Stmt {
public:
    virtual void execute(Environment &) = 0;
};

class LetStmt: Stmt {
private:
    shared_ptr<Token> name;
    shared_ptr<Expr> initializer;

public:
    void execute(Environment &) override;
};

class PrintStmt: Stmt {
private:
    shared_ptr<Expr> expr;

public:
    void execute(Environment &) override;
};

class InputStmt: Stmt {
private:
    shared_ptr<Token> name;

public:
    void execute(Environment &) override;
};

class GotoStmt: Stmt {
private:
    int lineNum;

public:
    void execute(Environment &) override;
};

class IfStmt: Stmt {
private:
    shared_ptr<Token> op;
    shared_ptr<Expr> expr1;
    shared_ptr<Expr> expr2;
    int lineNum;

public:
    void execute(Environment &) override;
};

class EndStmt: Stmt {
public:
    void execute(Environment &) override;
};

#endif // STMT_H
