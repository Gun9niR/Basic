#include "Stmt.h"
#include "MainWindow.h"

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
    Value value = initializer->evaluate(environment);

    environment.set(name->lexeme, value);

    environment.displayVariables();
}

PrintStmt::PrintStmt(ExprPtr expr): expr(expr) { }

void PrintStmt::execute(Environment& environment) {
    Value res = expr->evaluate(environment);
    MainWindow::getInstance().resultAppendRow(res.toResultString());
}

void PrintStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " PRINT"));

    expr->visualize(1);
}

InputStmt::InputStmt(TokenPtr name): name(name) { }

void InputStmt::receiveInput(const QString& inputText) {
    this->inputText = inputText;
}

void InputStmt::execute(Environment& environment) {
    QString varName = name->lexeme;
    MainWindow& mainWindow = MainWindow::getInstance();

    MainWindow::getInstance().waitInput();
    QEventLoop listener;
    connect(&mainWindow, &MainWindow::sendInput, this, &InputStmt::receiveInput);
    connect(&mainWindow, &MainWindow::sendInput, &listener, &QEventLoop::quit);
    listener.exec();
    disconnect(&mainWindow, &MainWindow::sendInput, this, &InputStmt::receiveInput);
    disconnect(&mainWindow, &MainWindow::sendInput, &listener, &QEventLoop::quit);
    // check if input is a number
    bool isNumber;
    int intVal = inputText.toInt(&isNumber);

    if (isNumber) {
        environment.set(varName, intVal);
    } else {
        MainWindow::getInstance().finishInput();
        throw InvalidInput();
    }

    MainWindow::getInstance().finishInput();
    environment.displayVariables();
}

void InputStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " INPUT"));

    MainWindow::getInstance().statementAppendRow("\t" + name->lexeme);
}

InputsStmt::InputsStmt(TokenPtr name): name(name) { }

void InputsStmt::receiveInput(const QString& inputText) {
    this->inputText = inputText;
}

void InputsStmt::execute(Environment& environment) {
    QString varName = name->lexeme;
    MainWindow& mainWindow = MainWindow::getInstance();

    MainWindow::getInstance().waitInput();
    QEventLoop listener;
    connect(&mainWindow, &MainWindow::sendInput, this, &InputsStmt::receiveInput);
    connect(&mainWindow, &MainWindow::sendInput, &listener, &QEventLoop::quit);
    listener.exec();
    disconnect(&mainWindow, &MainWindow::sendInput, this, &InputsStmt::receiveInput);
    disconnect(&mainWindow, &MainWindow::sendInput, &listener, &QEventLoop::quit);

    environment.set(varName, inputText);
    MainWindow::getInstance().finishInput();
    environment.displayVariables();
}

void InputsStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " INPUTS"));

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
    Value val1 = expr1->evaluate(environment);
    Value val2 = expr2->evaluate(environment);

    if (val1.isStr()) {
        throw new StringInCompoundExpr(val1.toString());
    }
    if (val2.isStr()) {
        throw new StringInCompoundExpr(val2.toString());
    }

    int intVal1 = val1.getIntVal();
    int intVal2 = val2.getIntVal();
    bool condition = false;

    switch (op->type) {
    case TokenType::EQUAL:
       condition = (intVal1 == intVal2);
        break;
    case TokenType::LESS:
        condition = (intVal1 < intVal2);
        break;
    case TokenType::GREATER:
        condition = (intVal1 > intVal2);
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

PrintfStmt::PrintfStmt(TokenPtr format, const vector<ExprPtr>& params): format(format), params(params) { }

void PrintfStmt::execute(Environment& environment) {
    // parser makes sure that value must be of type STRING
    QString formatStr = format->value.getStrVal();

    auto numOfPlaceholders = formatStr.count(PRINTF_PLACEHOLDER);
    auto numOfParams = static_cast<int>(params.size());
    if (numOfPlaceholders != numOfParams) {
        throw PrintfParamMismatch(numOfParams > numOfPlaceholders ?
                                      PrintfParamMismatch::ParamDifference::MORE :
                                      PrintfParamMismatch::ParamDifference::FEWER
                                      );
    }

    for (const ExprPtr& exprPtr: params) {
        Value value = exprPtr->evaluate(environment);
        QString valueStr = value.toResultString();
        formatStr.replace(formatStr.indexOf(PRINTF_PLACEHOLDER), 2, valueStr);
    }

    MainWindow::getInstance().resultAppendRow(formatStr);
}

void PrintfStmt::visualize(int lineNum) {
    MainWindow::getInstance().statementAppendRow(QString(QString::number(lineNum) + " PRINTF"));

    MainWindow::getInstance().statementAppendRow("\t" + format->value.toString());

    for (const ExprPtr& exprPtr: params) {
        exprPtr->visualize(1);
    }
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
