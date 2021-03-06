#ifndef EXPR_H
#define EXPR_H
#include "consts.h"

class Expr {
public:
    virtual double evaluate() = 0;
};

class ConstantExpr: Expr {
private:
    double val;

public:
    double evaluate() override;
};

class IdentifierExpr: Expr {
private:
    QString name;

public:
    double evaluate() override;
};

class CompoundExpr: Expr {
private:
    ExprType type;
    shared_ptr<Expr> left;
    shared_ptr<Expr> right;

public:
    double evaluate() override;
};

#endif // EXPR_H
