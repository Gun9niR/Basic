#include "Interpreter.h"
#include "qdebug.h"
#include "utils.h"
#include "qapplication.h"

Interpreter::Interpreter(): pc(0) {
}

void Interpreter::loadFile(QString fileName) {
    // if the file is empty, all the displays will not be cleared
    reset();
    emit clearDisplays();

    // open file
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);

    // read line by line, insert instructions as string into map
    // keep track of the line number in the file
    for (int fileLineNum = 1; !file.atEnd(); ++fileLineNum) {
        // get the trimmed string, with the line number
        QString str(file.readLine().trimmed());

        // process the string
        // the string can be a command or instruction
        // commands need to be run immediately
        handleRawInstruction(str);
    }

    file.close();
}

int Interpreter::getLineNumber(QString& str) {
    // str is not empty
    int lineNumber = 0;

    // check if str starts with a number
    if (!str[0].isDigit()) {
        throw QString("An instruction must start with a line number, ignoring this line");
    }

    // calculate line number,  string
    int len = str.length();
    int pos = 0;
    while (pos < len && str[pos].isDigit()) {
        lineNumber = lineNumber * 10 + str[pos].digitValue();
        ++pos;
    }

    // get the finally trimmed instruction
    str = str.mid(pos).trimmed();

    if (str.isEmpty()) {
        throw QString("Empty instruction, ignoring this line");
    }
    return lineNumber;
}

void Interpreter::handleRawInstruction(QString& str) {
    if (str.isEmpty()) {
        return;
    }

    // save a copy of str
    QString copy = str;

    // check if str is a command
    if (matchCommand(str)) {
        displayCode();
        runCommand(COMMANDS.find(str)->second);
        return;
    }

    // get the line number, remove it from the string
    int codeLineNum = 0;
    try {
        codeLineNum = getLineNumber(str);
    } catch (QString errMsg) {
        qDebug() << copy + ": " + errMsg;
        return;
    }

    // scan the string
    shared_ptr<QList<TokenPtr>> tokenList;
    try {
        tokenList = scanner.getTokens(str);
    } catch (QString errMsg) {
        qDebug() << QString::number(codeLineNum) + ": " + errMsg;
        return;
    }

    // parse the list of tokens
    StmtPtr stmt;
    try {
        stmt = parser.getStmt(tokenList);
    } catch (QString errMsg) {
        qDebug() << QString::number(codeLineNum) + ": " + errMsg;
        return;
    }

    // add the instruction to three maps
    rawInstruction[codeLineNum] = str;
    tokens[codeLineNum] = tokenList;

    // display code string and syntax tree
    displayCode();
}

void Interpreter::reset() {
    // reset all properties
    rawInstruction.clear();
    tokens.clear();
    stmts.clear();
    environment.reset();

    // close the file
    if (file.isOpen()) {
        file.close();
    }
    file.setFileName("");
}


void Interpreter::displayCode() {
    // clear codeDisplay first
    // align the code number
    emit clearDisplays();

    if (rawInstruction.empty()) {
        return;
    }

    int maxLineNum = rawInstruction.rbegin()->first;
    int maxDigits = getDigits(maxLineNum);

    // emit signal to update content in codeDisplay
    for (auto i = rawInstruction.begin(); i != rawInstruction.end(); ++i ) {
        emit codeAppendRow(QString::number(i->first).rightJustified(maxDigits, '0') + " " + i->second);
    }
}

bool Interpreter::matchCommand(QString& str) {
    // check if str is a command
    return COMMANDS.count(str);
}

// run the command
void Interpreter::runCommand(CommandType type) {
    switch(type) {
    case CommandType::RUN:
        qDebug() << "Command: RUN";
        break;
    case CommandType::LOAD:
        qDebug() << "Command: LOAD";
        break;
    case CommandType::CLEAR:
        emit clickClearButton();
        break;
    case CommandType::HELP:
        qDebug() << "Command: HELP";
        break;
    case CommandType::QUIT:
        QApplication::quit();
        break;
    }
}

void Interpreter::showTokens() {
    for (auto line = tokens.begin(); line != tokens.end(); ++line) {
        auto lineNum = line->first;
        qDebug() << "On line " << lineNum;
        auto list = *(line->second);
        for (auto token = list.begin(); token != list.end(); ++token) {
            qDebug() << **token;
        }
    }
}

void Interpreter::interpret() {
    showTokens();
    return;
}
