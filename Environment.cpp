#include "Environment.h"

Environment::Environment() {
    symbolTable.clear();
}

void Environment::set(const QString& name, const Value& value) {
    symbolTable[name] = value;
}

Value Environment::get(const QString& name) {
    return symbolTable[name];
}

bool Environment::isDefined(const QString& name) {
    return symbolTable.count(name);
}

void Environment::reset() {
    symbolTable.clear();
}
