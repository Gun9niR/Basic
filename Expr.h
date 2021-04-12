#ifndef EXPR_H
#define EXPR_H

#include "consts.h"
#include "Environment.h"
#include "Token.h"

class Expr {
public:
    virtual int evaluate(Environment &) = 0;
    virtual void visualize(int) = 0;
};

typedef shared_ptr<Expr> ExprPtr;

class ConstantExpr: public Expr {
private:
    const int val;

public:
    ConstantExpr(int v);
    int evaluate(Environment &) override;
    void visualize(int) override;
};

class IdentifierExpr: public Expr {
private:
    const QString name;

public:
    IdentifierExpr(QString str);
    int evaluate(Environment &) override;
    void visualize(int) override;
};

class CompoundExpr: public Expr {
private:
    // type MINUS and nullptr on left means negative
    const TokenPtr op;
    const ExprPtr left;
    const ExprPtr right;

public:
    CompoundExpr(TokenPtr t, ExprPtr l, ExprPtr r);
    int evaluate(Environment &) override;
    void visualize(int) override;
};
#endif // EXPR_H
