#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "consts.h"
#include "Value.h"

class Environment {
public:
    void set(const QString& name, const Value& value);

    Value get(const QString& name);

    bool isDefined(const QString& name);

    Environment();

    void reset();

private:
    map<QString, Value> symbolTable;
};

#endif // ENVIRONMENT_H
