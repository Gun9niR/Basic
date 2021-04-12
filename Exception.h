#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "consts.h"

class Exception {
public:
    virtual QString getMsg() const = 0 ;
};

class DivisionByZero: public Exception {
public:
    QString getMsg() const override;
};

class JumpSignal: public Exception {
private:
    int lineNum;

public:
    JumpSignal(int);
    int getJumpDest() const;
    QString getMsg() const override;
};

class NoSuchVariable: public Exception {
private:
    QString name;

public:
    NoSuchVariable(QString);
    QString getMsg() const override;
};

class EndSignal: public Exception {
public:
    QString getMsg() const override;
};

class ScanOrParseError: public Exception {
private:
    QString errorMsg;

public:
   ScanOrParseError(QString);
   QString getMsg() const override;
};

class InvalidInput: public Exception {
public:
    QString getMsg() const override;
};

class PowerError: public Exception {
private:
    QString errorMsg;

public:
    PowerError(QString errorMsg);
    QString getMsg() const override;
};

#endif // EXCEPTION_H
