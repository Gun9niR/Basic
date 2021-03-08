#include "Exception.h"

QString DivisionByZero::getMsg() {
    return "Division by zero";
}

JumpSignal::JumpSignal(int lineNum): lineNum(lineNum) {}

QString JumpSignal::getMsg() {
    return "Line " + QString::number(lineNum) + "does not exist";
}

int JumpSignal::getJumpDest() {
    return lineNum;
}

NoSuchVariable::NoSuchVariable(QString name): name(name) {}

QString NoSuchVariable::getMsg() {
    return "Undefined variable: " + name;
}

QString EndSignal::getMsg() {
    return "Program ended successfully";
}
