#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "consts.h"

class Environment {
public:
    void set(QString name, double value);
    double get(QString name);
    bool isDefined(QString name);
    void reset();

private:
    map<QString, double> symbolTable;
};

#endif // ENVIRONMENT_H
