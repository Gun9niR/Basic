#include "Exception.h"

QString DivisionByZero::getMsg() const {
    return "Division by zero!";
}

JumpSignal::JumpSignal(int lineNum): lineNum(lineNum) {}

QString JumpSignal::getMsg() const {
    return "Line " + QString::number(lineNum) + " does not exist!";
}

int JumpSignal::getJumpDest() const {
    return lineNum;
}

NoSuchVariable::NoSuchVariable(const QString& name): name(name) {}

QString NoSuchVariable::getMsg() const {
    return "Undefined variable: " + name;
}

QString EndSignal::getMsg() const {
    return "";
}

ScanOrParseError::ScanOrParseError(const QString& errorMsg): errorMsg(errorMsg) {}

QString ScanOrParseError::getMsg() const {
    return errorMsg;
}

QString InvalidInput::getMsg() const {
    return "Input must be an integer or a valid string!";
}

PowerError::PowerError(const QString& errorMsg): errorMsg(errorMsg) { }

QString PowerError::getMsg() const {
    return errorMsg;
}

PrintfParamMismatch::PrintfParamMismatch(ParamDifference diff): diff(diff) { }

QString PrintfParamMismatch::getMsg() const {
    QString diffStr = diff == MORE ? "Too many " : "Too few ";
    return diffStr + "parameters are provided!";
}

StringInCompoundExpr::StringInCompoundExpr(const QString& lexeme): lexeme(lexeme) { }

QString StringInCompoundExpr::getMsg() const {
    return "String cannot be involved in computations!";
}
