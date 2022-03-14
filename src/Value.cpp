#include "Value.h"

const unordered_map<ValueType, QString> Value::TYPE_NAME {
    { ValueType::INT, "INT" },
    { ValueType::STR, "STR" },
    { ValueType::NONE, "NONE" },
};

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

QString Value::getTypeName() const {
    return TYPE_NAME.at(type);
}

QString Value::getStrVal() const {
    return strVal;
}

int Value::getIntVal() const {
    return type == ValueType::INT ? intVal : 0;
}
