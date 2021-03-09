#ifndef STMT_H
#define STMT_H

#include "consts.h"
#include "Environment.h"
#include "Token.h"
#include "Expr.h"

class Stmt: public QObject {
    Q_OBJECT

public:
    virtual void execute(Environment &) = 0;
    virtual void visualize(int) = 0;

signals:
    void statementAppendRow(QString str);
};

typedef shared_ptr<Stmt> StmtPtr;

class RemStmt: public Stmt {
private:
    const TokenPtr comment;

public:
    RemStmt(TokenPtr);
    void execute(Environment &) override;
    void visualize(int) override;
};

class LetStmt: public Stmt {
private:
    const TokenPtr name;
    const ExprPtr initializer;

public:
    LetStmt(TokenPtr, ExprPtr);
    void execute(Environment &) override;
    void visualize(int) override;
};

class PrintStmt: public Stmt {
    Q_OBJECT
private:
    const ExprPtr expr;

public:
    PrintStmt(ExprPtr);
    void execute(Environment &) override;
    void visualize(int) override;

signals:
    void resultAppendRow(QString);
};

class InputStmt: public Stmt {
    Q_OBJECT
private:
    const TokenPtr name;
    int input;

public slots:
    void receiveInput(int);

public:
    InputStmt(TokenPtr name);
    void execute(Environment &) override;
    void visualize(int) override;
};

class GotoStmt: public Stmt {
private:
    const int lineNum;

public:
    GotoStmt(int lineNum);
    void execute(Environment &) override;
    void visualize(int lineNum) override;
};

class IfStmt: public Stmt {
private:
    const TokenPtr op;
    const ExprPtr expr1;
    const ExprPtr expr2;
    const int lineNum;

public:
    IfStmt(TokenPtr, ExprPtr, ExprPtr, int);
    void execute(Environment &) override;
    void visualize(int) override;
};

class EndStmt: public Stmt {
public:
    EndStmt();
    void execute(Environment &) override;
    void visualize(int) override;
};

#endif // STMT_H
