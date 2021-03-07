#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "consts.h"
#include "Token.h"
#include "Environment.h"

class Interpreter: public QObject {
    Q_OBJECT

private:
    Environment environment;
    int pc;

public:
    Interpreter();

    void interpret();
};
#endif // INTERPRETER_H
