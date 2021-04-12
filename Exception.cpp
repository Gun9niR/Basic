#include "Exception.h"

QString DivisionByZero::getMsg() const {
    return "Division by zero";
}

JumpSignal::JumpSignal(int lineNum): lineNum(lineNum) {}

QString JumpSignal::getMsg() const {
    return "Line " + QString::number(lineNum) + " does not exist";
}

int JumpSignal::getJumpDest() const {
    return lineNum;
}

NoSuchVariable::NoSuchVariable(QString name): name(name) {}

QString NoSuchVariable::getMsg() const {
    return "Undefined variable: " + name;
}

QString EndSignal::getMsg() const {
    return "";
}

ScanOrParseError::ScanOrParseError(QString errorMsg): errorMsg(errorMsg) {}

QString ScanOrParseError::getMsg() const {
    return errorMsg;
}

QString InvalidInput::getMsg() const {
    return "Input must be an integer!";
}

PowerError::PowerError(QString errorMsg): errorMsg(errorMsg) { }

QString PowerError::getMsg() const {
    return errorMsg;
}
