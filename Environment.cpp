#include "Environment.h"

Variable::Variable(TimeStamp t, const QString& n, const Value& v): timeStamp(t), name(n), value(v) {}

Environment::Environment(): timeStamp(0) {
    variables.clear();
}

void Environment::set(const QString& name, const Value& value) {
    variables[name] = value;
    timeStamps[name] = timeStamp++;
}

Value Environment::get(const QString& name) {
    return variables[name];
}

bool Environment::isDefined(const QString& name) {
    return variables.count(name);
}

void Environment::reset() {
    variables.clear();
    timeStamps.clear();
    timeStamp = 0;
}

void Environment::displayVariables() const {
    MainWindow& mainWindow = MainWindow::getInstance();
    mainWindow.clearEnvironment();

    // sort variables by order of time
    vector<Variable> sortedVariables;
    for (const auto& variable: variables) {
        QString variableName = variable.first;
        sortedVariables.emplace_back(timeStamps.at(variableName), variableName, variable.second);
    }

    sort(sortedVariables.begin(),
         sortedVariables.end(),
         [](const Variable& v1, const Variable& v2) {
        return v1.timeStamp < v2.timeStamp;
    });

    // display variables
    QString format = "%1: %2 = %3";
    for (const auto& sortedVariable: sortedVariables) {
        mainWindow.environmentAppendRow(
                    format.arg(
                        sortedVariable.name,
                        sortedVariable.value.getTypeName(),
                        sortedVariable.value.toString()
                        )
                    );
    }
}
