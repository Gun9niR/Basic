#ifndef VALUE_H
#define VALUE_H

#include "consts.h"

class Value {
private:
    static const unordered_map<ValueType, QString> TYPE_NAME;

    ValueType type;
    int intVal;
    QString strVal;

public:
    Value();

    Value(const QString&);

    Value(int);

    // convert value to string that is displayed in message, string is surrounded with quote
    QString toString() const;

    // convert value to string that is used for display as program result
    QString toResultString() const;

    QString getTypeName() const;

    bool isStr() const;

    QString getStrVal() const;

    int getIntVal() const;

public:
    static Value NO_VALUE;
};

#endif // VALUE_H
