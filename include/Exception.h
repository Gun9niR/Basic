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
    NoSuchVariable(const QString&);
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
   ScanOrParseError(const QString&);
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
    PowerError(const QString&);
    QString getMsg() const override;
};

class PrintfParamMismatch: public Exception {
public:
    typedef enum {MORE, FEWER} ParamDifference;

private:
    ParamDifference diff;

public:
    PrintfParamMismatch(ParamDifference diff);
    QString getMsg() const override;

};

class StringInCompoundExpr: public Exception {
private:
    // quote might change
    QString lexeme;

public:
    StringInCompoundExpr(const QString&);
    QString getMsg() const override;
};

#endif // EXCEPTION_H
