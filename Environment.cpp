#include "Environment.h"

Environment::Environment() {
    symbolTable.clear();
}

void Environment::set(QString name, int value) {
    symbolTable[name] = value;
}

int Environment::get(QString name) {
    return symbolTable[name];
}

bool Environment::isDefined(QString name) {
    return symbolTable.count(name);
}

void Environment::reset() {
    symbolTable.clear();
}
