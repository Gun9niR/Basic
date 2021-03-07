#include "Expr.h"

double ConstantExpr::evaluate(Environment& environment) {
    return val;
}

double IdentifierExpr::evaluate(Environment& environment) {
    if (environment.isDefined(name)) {
        throw QString("No such variable: " + name);
    }
    return environment.get(name);
}

double CompoundExpr::evaluate(Environment& environment) {
    switch(type) {
    case TokenType::PLUS:
        return left->evaluate(environment) + right->evaluate(environment);
    case TokenType::MINUS:
        if (left == nullptr) {
            return -right->evaluate(environment);
        }
        return left->evaluate(environment) - right->evaluate(environment);
    case TokenType::STAR:
        return left->evaluate(environment) * right->evaluate(environment);
    case TokenType::SLASH:
        return left->evaluate(environment) / right->evaluate(environment);
    case TokenType::POWER:
        return pow(left->evaluate(environment), right->evaluate(environment));
    default:
        throw QString("Parsing error");
    }
}

ConstantExpr::ConstantExpr(double v): val(v) {}

IdentifierExpr::IdentifierExpr(QString str): name(str) {}

CompoundExpr::CompoundExpr(TokenType t, ExprPtr l, ExprPtr r): type(t), left(l), right(r) {}
