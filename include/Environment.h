#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "consts.h"
#include "Value.h"
#include "MainWindow.h"

class Environment {
public:
    Environment();

    void set(const QString& name, const Value& value);

    Value get(const QString& name);

    bool isDefined(const QString& name);

    void reset();

    void displayVariables() const;

private:
    TimeStamp timeStamp;
    unordered_map<QString, Value> variables;
    unordered_map<QString, TimeStamp> timeStamps;
};

typedef struct Variable {
    TimeStamp timeStamp;
    QString name;
    Value value;

    Variable(TimeStamp, const QString&, const Value&);
} Variable;
#endif // ENVIRONMENT_H
