#include "Stmt.h"
#include "mainwindow.h"
#include "Exception.h"
#include "QEventLoop"

RemStmt::RemStmt(TokenPtr comment): comment(comment) {
    connect(this, &RemStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
}

void RemStmt::execute(Environment& environment) {
    return;
}

void RemStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " REM"));
    // append comment
    emit statementAppendRow("\t" + comment->lexeme);
}

LetStmt::LetStmt(TokenPtr name, ExprPtr initializer): name(name), initializer(initializer) {
    connect(this, &LetStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
}

void LetStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " LET ="));

    // append identifier
    emit statementAppendRow("\t" + name->lexeme);
    initializer->visualize(1);
}

void LetStmt::execute(Environment& environment) {
    double value = initializer->evaluate(environment);

    environment.set(name->lexeme, value);
}

PrintStmt::PrintStmt(ExprPtr expr): expr(expr) {
    connect(this, &PrintStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
    connect(this, &PrintStmt::resultAppendRow, &MainWindow::getInstance(), &MainWindow::resultAppendRow);
}

void PrintStmt::execute(Environment& environment) {
    double res = expr->evaluate(environment);
    emit resultAppendRow(QString::number(res));
}

void PrintStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " PRINT"));

    expr->visualize(1);
}

InputStmt::InputStmt(TokenPtr name): name(name) {
    connect(this, &InputStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
    connect(&MainWindow::getInstance(), &MainWindow::sendInput, this, &InputStmt::receiveInput);
}

void InputStmt::receiveInput(int x) {
    input = x;
}

void InputStmt::execute(Environment& environment) {
    QString varName = name->lexeme;
    MainWindow::getInstance().waitInput();
    QEventLoop listener;
    connect(&MainWindow::getInstance(), &MainWindow::sendInput, &listener, &QEventLoop::quit);
    listener.exec();
    environment.set(varName, input);
    MainWindow::getInstance().finishInput();
}

void InputStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " INPUT"));

    emit statementAppendRow("\t" + name->lexeme);
}

GotoStmt::GotoStmt(int lineNum): lineNum(lineNum) {
    connect(this, &GotoStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
}

void GotoStmt::execute(Environment& environment) {
    throw JumpSignal(lineNum);
}

void GotoStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " GOTO"));

    emit statementAppendRow("\t" + QString::number(lineNum));
}

IfStmt::IfStmt(TokenPtr op, ExprPtr e1, ExprPtr e2, int lineNum): op(op), expr1(e1), expr2(e2), lineNum(lineNum) {
    connect(this, &IfStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
}

void IfStmt::execute(Environment& environment) {
    double val1 = expr1->evaluate(environment);
    double val2 = expr2->evaluate(environment);
    bool condition = false;

    switch (op->type) {
    case TokenType::EQUAL:
       condition = (val1 == val2);
        break;
    case TokenType::LESS:
        condition = (val1 < val2);
        break;
    case TokenType::GREATER:
        condition = (val1 > val2);
        break;
    }

    if (condition) {
        throw JumpSignal(lineNum);
    }
}

void IfStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " IF THEN"));

    expr1->visualize(1);

    emit statementAppendRow("\t" + op->lexeme);

    expr2->visualize(1);

    emit statementAppendRow("\t" + QString::number(this->lineNum));
}

EndStmt::EndStmt() {
    connect(this, &EndStmt::statementAppendRow, &MainWindow::getInstance(), &MainWindow::statementAppendRow);
}

void EndStmt::execute(Environment& environment) {
    throw EndSignal();
}

void EndStmt::visualize(int lineNum) {
    emit statementAppendRow(QString(QString::number(lineNum) + " END"));
}
