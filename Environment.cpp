#include "Environment.h"

void Environment::set(QString name, double value) {
    symbolTable[name] = value;
}

double Environment::get(QString name) {
    return symbolTable[name];
}

bool Environment::isDefined(QString name) {
    return symbolTable.count(name);
}

void Environment::reset() {
    symbolTable.clear();
}
