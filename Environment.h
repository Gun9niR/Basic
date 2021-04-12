#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "consts.h"

class Environment {
public:
    void set(QString name, int value);

    int get(QString name);

    bool isDefined(QString name);

    Environment();

    void reset();

private:
    map<QString, int> symbolTable;
};

#endif // ENVIRONMENT_H
