#ifndef VALUE_H
#define VALUE_H

#include "consts.h"

class Value {
private:
    ValueType type;
    int intVal;
    QString strVal;



public:
    Value();

    Value(const QString&);

    Value(int);

    // convert value to string that is displayed in message, string is surrounded with quote
    QString toString() const;

    QString toResultString() const;

    bool isStr() const;

    QString getStrVal() const;

    int getIntVal() const;

public:
    static Value NO_VALUE;
};

#endif // VALUE_H
