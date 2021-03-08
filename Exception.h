#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "consts.h"

class Exception {
public:
    virtual QString getMsg() = 0;
};

class DivisionByZero: public Exception {
public:
    QString getMsg();
};

class JumpSignal: public Exception {
private:
    int lineNum;

public:
    JumpSignal(int);
    int getJumpDest();
    QString getMsg();
};

class NoSuchVariable: public Exception {
private:
    QString name;

public:
    NoSuchVariable(QString);
    QString getMsg();
};

class EndSignal: public Exception {
public:
    QString getMsg() override;
};

#endif // EXCEPTION_H
