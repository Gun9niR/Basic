#include "Expr.h"
#include "MainWindow.h"
#include "Exception.h"

ConstantExpr::ConstantExpr(int intVal): val(intVal) { }

ConstantExpr::ConstantExpr(const QString& str): val(str) { }

ConstantExpr::ConstantExpr(const Value& val): val(val) { }

IdentifierExpr::IdentifierExpr(QString str): name(str) { }

CompoundExpr::CompoundExpr(TokenPtr t, ExprPtr l, ExprPtr r): op(t), left(l), right(r) { }

Value ConstantExpr::evaluate(Environment& environment) {
    return val;
}

void ConstantExpr::visualize(int indents) {
    QString strToAppend;

    for (int i = 0; i < indents; ++i) {
        strToAppend += SPACE;
    }

    // append number
    strToAppend += val.toString();

    MainWindow::getInstance().statementAppendRow(strToAppend);
}

Value IdentifierExpr::evaluate(Environment& environment) {
    if (!environment.isDefined(name)) {
        throw NoSuchVariable(name);
    }
    return environment.get(name);
}

void IdentifierExpr::visualize(int indents) {
    QString strToAppend;

    // appendTabs
    for (int i = 0; i < indents; ++i) {
        strToAppend += SPACE;
    }

    // append identifier
    strToAppend += name;

    MainWindow::getInstance().statementAppendRow(strToAppend);
}

Value CompoundExpr::evaluate(Environment& environment) {
    Value valLeft = left ? left->evaluate(environment) : Value::NO_VALUE;
    Value valRight = right->evaluate(environment);

    if (valLeft.isStr()) {
        throw StringInCompoundExpr(valLeft.toString());
    }
    if (valRight.isStr()) {
        throw StringInCompoundExpr(valRight.toString());
    }

    int intLeft = valLeft.getIntVal();
    int intRight = valRight.getIntVal();

    switch(op->type) {
    case TokenType::PLUS:
        return intLeft + intRight;
    case TokenType::MINUS:
        return intLeft - intRight;
    case TokenType::STAR:
        return intLeft * intRight;
    case TokenType::SLASH:
        if (!intRight) {
            throw DivisionByZero();
        }
        return intLeft / intRight;
    case TokenType::POWER:
        if (!intLeft && !intRight) {
            throw PowerError("0 ^ 0 is not a number!");
        }
        return pow(intLeft, intRight);
    default:
        throw QString("Parsing error");
    }
}

void CompoundExpr::visualize(int indents) {
    QString strToAppend;

    // appendTabs
    for (int i = 0; i < indents; ++i) {
        strToAppend += SPACE;
    }

    // append identifier
    strToAppend += op->lexeme;
    MainWindow::getInstance().statementAppendRow(strToAppend);

    if (left != nullptr) {
        left->visualize(indents + 1);
    }
    right->visualize(indents + 1);
}
