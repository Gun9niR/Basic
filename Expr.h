#ifndef EXPR_H
#define EXPR_H

#include "consts.h"
#include "Environment.h"

class Expr {
public:
    virtual double evaluate(Environment &) = 0;
};

typedef shared_ptr<Expr> ExprPtr;

class ConstantExpr: Expr {
private:
    double val;
    bool isNegative;

public:
    ConstantExpr(double v, bool n = false);
    double evaluate(Environment &) override;
};

class IdentifierExpr: Expr {
private:
    QString name;

public:
    IdentifierExpr(QString str);
    double evaluate(Environment &) override;
};

class CompoundExpr: Expr {
private:
    ExprType type;
    ExprPtr left;
    ExprPtr right;

public:
    CompoundExpr(ExprType t, ExprPtr l, ExprPtr r);
    double evaluate(Environment &) override;
};
#endif // EXPR_H
