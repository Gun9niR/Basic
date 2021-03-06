#include "Expr.h"

double ConstantExpr::evaluate() {
    return val;
}

double IdentifierExpr::evaluate() {
    return 0;
}

double CompoundExpr::evaluate() {
    switch(type) {
    case ExprType::ADD:
        return left->evaluate() + right->evaluate();
    case ExprType::SUB:
        return left->evaluate() - right->evaluate();
    case ExprType::MULT:
        return left->evaluate() * right->evaluate();
    case ExprType::DIV:
        return left->evaluate() / right->evaluate();
    case ExprType::POW:
        return 0;
    }
}
