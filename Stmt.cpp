#include "Stmt.h"
#include "mainwindow.h"
#include "Exception.h"
#include "QEventLoop"

RemStmt::RemStmt(TokenPtr comment): comment(comment) { }

void RemStmt::execute(Environment& environment) {
    return;
}

void RemStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " REM"));
    // append comment
    MainWindow::getInstance().statementAppendRow("\t" + comment->lexeme);
}

LetStmt::LetStmt(TokenPtr name, ExprPtr initializer): name(name), initializer(initializer) { }

void LetStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " LET ="));

    // append identifier
    MainWindow::getInstance().statementAppendRow("\t" + name->lexeme);
    initializer->visualize(1);
}

void LetStmt::execute(Environment& environment) {
    int value = initializer->evaluate(environment);

    environment.set(name->lexeme, value);
}

PrintStmt::PrintStmt(ExprPtr expr): expr(expr) { }

void PrintStmt::execute(Environment& environment) {
    int res = expr->evaluate(environment);
    MainWindow::getInstance().resultAppendRow(QString::number(res));
}

void PrintStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " PRINT"));

    expr->visualize(1);
}

InputStmt::InputStmt(TokenPtr name): name(name), isInputValid(true) {
    connect(&MainWindow::getInstance(), &MainWindow::sendInput, this, &InputStmt::receiveInput);
    connect(&MainWindow::getInstance(), &MainWindow::sendInvalidInput, this, &InputStmt::receiveInvalidInput);
}

void InputStmt::receiveInput(int x) {
    input = x;
}

void InputStmt::receiveInvalidInput() {
    isInputValid = false;
}

void InputStmt::execute(Environment& environment) {
    QString varName = name->lexeme;

    MainWindow::getInstance().waitInput();
    QEventLoop listener;
    connect(&MainWindow::getInstance(), &MainWindow::sendInput, &listener, &QEventLoop::quit);
    connect(&MainWindow::getInstance(), &MainWindow::sendInvalidInput, &listener, &QEventLoop::quit);
    listener.exec();
    if (!isInputValid) {
        MainWindow::getInstance().finishInput();
        throw InvalidInput();
    }
    environment.set(varName, input);
    MainWindow::getInstance().finishInput();
}

void InputStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " INPUT"));

    MainWindow::getInstance().statementAppendRow("\t" + name->lexeme);
}

GotoStmt::GotoStmt(int lineNum): lineNum(lineNum) { }

void GotoStmt::execute(Environment& environment) {
    throw JumpSignal(lineNum);
}

void GotoStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " GOTO"));

    MainWindow::getInstance().statementAppendRow("\t" + QString::number(lineNum));
}

IfStmt::IfStmt(TokenPtr op, ExprPtr e1, ExprPtr e2, int lineNum): op(op), expr1(e1), expr2(e2), lineNum(lineNum) { }

void IfStmt::execute(Environment& environment) {
    int val1 = expr1->evaluate(environment);
    int val2 = expr2->evaluate(environment);
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
    default:
        break;
    }

    if (condition) {
        throw JumpSignal(lineNum);
    }
}

void IfStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " IF THEN"));

    expr1->visualize(1);

    MainWindow::getInstance().statementAppendRow("\t" + op->lexeme);

    expr2->visualize(1);

    MainWindow::getInstance().statementAppendRow("\t" + QString::number(this->lineNum));
}

EndStmt::EndStmt() { }

void EndStmt::execute(Environment& environment) {
    throw EndSignal();
}

void EndStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " END"));
}

ErrorStmt::ErrorStmt(QString errorMsg): errorMsg(errorMsg) { }

void ErrorStmt::execute(Environment &) {
    throw ScanOrParseError(errorMsg);
}

void ErrorStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString::number(lineNum) + ": " + errorMsg);
}
