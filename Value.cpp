#include "Value.h"

Value Value::NO_VALUE = Value();

Value::Value(): type(ValueType::NONE) { }

Value::Value(const QString& strVal): type(ValueType::STR), strVal(strVal) { }

Value::Value(int intVal): type(ValueType::INT), intVal(intVal) { }

bool Value::isStr() const {
    return type == ValueType::STR;
}

QString Value::toString() const {
    switch (type) {
    case ValueType::INT:
        return QString::number(intVal);
    case ValueType::STR:
        return '"' + strVal + '"';
    default:
        return "NO_VALUE";
    }
}

QString Value::toResultString() const {
    switch (type) {
    case ValueType::INT:
        return QString::number(intVal);
    case ValueType::STR:
        return strVal;
    default:
        return "NO_VALUE";
    }
}

QString Value::getStrVal() const {
    return strVal;
}

int Value::getIntVal() const {
    return type == ValueType::INT ? intVal : 0;
}
