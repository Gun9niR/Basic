#include "Expr.h"
#include "mainwindow.h"
#include "Exception.h"

ConstantExpr::ConstantExpr(int v): val(v) { }

IdentifierExpr::IdentifierExpr(QString str): name(str) { }

CompoundExpr::CompoundExpr(TokenPtr t, ExprPtr l, ExprPtr r): op(t), left(l), right(r) { }

int ConstantExpr::evaluate(Environment& environment) {
    return val;
}

void ConstantExpr::visualize(int indents) {
    QString strToAppend = "";

    // appendTabs
    for (int i = 0; i < indents; ++i) {
        strToAppend += "\t";
    }

    // append number
    strToAppend += QString::number(val);


    MainWindow::getInstance().statementAppendRow(strToAppend);
}

int IdentifierExpr::evaluate(Environment& environment) {
    if (!environment.isDefined(name)) {
        throw NoSuchVariable(name);
    }
    return environment.get(name);
}

void IdentifierExpr::visualize(int indents) {
    QString strToAppend = "";

    // appendTabs
    for (int i = 0; i < indents; ++i) {
        strToAppend += "\t";
    }

    // append identifier
    strToAppend += name;

    MainWindow::getInstance().statementAppendRow(strToAppend);
}

int CompoundExpr::evaluate(Environment& environment) {
    int valLeft = left ? left->evaluate(environment) : 0;
    int valRight = right->evaluate(environment);
    switch(op->type) {
    case TokenType::PLUS:
        return valLeft + valRight;
    case TokenType::MINUS:
        return valLeft - valRight;
    case TokenType::STAR:
        return valLeft * valRight;
    case TokenType::SLASH:
        if (!valRight) {
            throw DivisionByZero();
        }
        return valLeft / valRight;
    case TokenType::POWER:
        if (!valLeft && !valRight) {
            throw PowerError("0 ^ 0 is not a number!");
        }
        return pow(valLeft, valRight);
    default:
        throw QString("Parsing error");
    }
}

void CompoundExpr::visualize(int indents) {
    QString strToAppend = "";

    // appendTabs
    for (int i = 0; i < indents; ++i) {
        strToAppend += "\t";
    }

    // append identifier
    strToAppend += op->lexeme;
    MainWindow::getInstance().statementAppendRow(strToAppend);

    if (left != nullptr) {
        left->visualize(indents + 1);
    }
    right->visualize(indents + 1);
}
