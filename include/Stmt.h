#ifndef STMT_H
#define STMT_H

#include "consts.h"
#include "Exception.h"
#include "Environment.h"
#include "Token.h"
#include "Expr.h"
#include "util.h"

class Stmt {
public:
    virtual void execute(Environment &) = 0;
    virtual void visualize(int) = 0;
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
private:
    const ExprPtr expr;

public:
    PrintStmt(ExprPtr);
    void execute(Environment &) override;
    void visualize(int) override;
};

class InputStmt: public QObject, public Stmt {
    Q_OBJECT
private:
    const TokenPtr name;
    QString inputText;
public slots:
    void receiveInput(const QString&);

public:
    InputStmt(TokenPtr name);
    void execute(Environment &) override;
    void visualize(int) override;
};

class InputsStmt: public QObject, public Stmt {
    Q_OBJECT
private:
    const TokenPtr name;
    QString inputText;
public slots:
    void receiveInput(const QString&);

public:
    InputsStmt(TokenPtr name);
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

class PrintfStmt: public Stmt {
private:
    const TokenPtr format;
    const vector<ExprPtr> params;

public:
    PrintfStmt(TokenPtr, const vector<ExprPtr>&);
    void execute(Environment &) override;
    void visualize(int) override;
};

class EndStmt: public Stmt {
public:
    EndStmt();
    void execute(Environment &) override;
    void visualize(int) override;
};

class ErrorStmt: public Stmt {
private:
    const QString errorMsg;

public:
    ErrorStmt(QString);
    void execute(Environment &) override;
    void visualize(int) override;
};

#endif // STMT_H
