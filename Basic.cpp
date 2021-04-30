#include "Basic.h"

Basic::~Basic() { }

Basic::Basic() { }

Basic& Basic::getInstance() {
    static Basic basic;
    return basic;
}

void Basic::startDebug() {
    interpreter = make_unique<Interpreter>(rawInstruction, environment);
    interpreter->startDebugging();
}

void Basic::finishDebug() {
    interpreter.reset();
}

void Basic::interpretAll() {
    interpreter = make_unique<Interpreter>(rawInstruction, environment);
    interpreter->interpretAll();
    interpreter.reset();
}

void Basic::interpretRest() {
    interpreter->interpretRest();
}

void Basic::debugStep() {
    interpreter->debugStep();
}

void Basic::loadFile(QString fileName) {
    // if the file is empty, all the displays will not be cleared
    reset();
    MainWindow::getInstance().clearDisplays();

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
        isLoadingFile = true;
        handleRawInstruction(str);
        isLoadingFile = false;
    }

    file.close();
}

LineNum Basic::getLineNumber(QString& str) {
    // str is not empty
    int lineNumber = 0;

    // check if str starts with a number
    if (!str[0].isDigit()) {
        throw QString("An instruction must start with a line number");
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

    return lineNumber;
}

void Basic::handleRawInstruction(QString& str) {
    // string is trimmed already
    if (str.isEmpty()) {
        return;
    }

    // save a copy of str for error message
    QString copy = str;

    // check if str is a command
    if (matchCommand(str)) {
        runCommand(COMMANDS.find(str)->second);
        return;
    }

    // check if str is among the statements that can be executed
    QString oneOfTheThreeStmts = nullptr;
    if (matchStmtWithoutLineNumber(str, oneOfTheThreeStmts)) {
        if (isLoadingFile) {
            MainWindow::getInstance().errorAppendRow(oneOfTheThreeStmts + " statement must follow a line number in the file!");
            return;
        } else {
            Interpreter::interpret(str, environment);
            return;
        }
    }

    // get the line number, remove it from the string
    LineNum codeLineNum = 0;
    try {
        codeLineNum = getLineNumber(str);
    } catch (QString errMsg) {
        MainWindow::getInstance().errorAppendRow(copy + ": " + errMsg);
        return;
    }

    if (codeLineNum == 0) {
        MainWindow::getInstance().errorAppendRow(copy + ": Line number must be a positive integer.");
        return;
    }
    if (codeLineNum > 1000000) {
        MainWindow::getInstance().errorAppendRow(copy + ": Line number must not exceed 1000000.");
        return;
    }

    // check for empty instruction
    if (str.isEmpty()) {
        if (rawInstruction.count(codeLineNum)) {
            rawString.erase(codeLineNum);
            rawInstruction.erase(codeLineNum);
            displayCode();
            return;
        } else {
            return;
        }
    }
    // add to raw instruction
    rawInstruction[codeLineNum] = str;
    rawString[codeLineNum] = copy;
    displayCode();
}

void Basic::reset() {
    // reset all properties
    rawInstruction.clear();
    rawString.clear();

    // close the file
    if (file.isOpen()) {
        file.close();
    }
    file.setFileName("");
}

int Basic::getDigits(int x) {
    int ret = 0;

    while (x) {
        ++ret;
        x /= 10;
    }

    return ret;
}

void Basic::displayInstruction() {
    // clear codeDisplay first
    MainWindow::getInstance().clearCode();

    // align the code number
    if (rawInstruction.empty()) {
        return;
    }

    int maxLineNum = rawInstruction.rbegin()->first;
    int maxDigits = getDigits(maxLineNum);

    // update content in codeDisplay
    for (auto i = rawInstruction.begin(); i != rawInstruction.end(); ++i ) {
        MainWindow::getInstance().codeAppendRow(QString::number(i->first).rightJustified(maxDigits, '0') + " " + i->second);
    }
}

void Basic::displayCode() {
    MainWindow::getInstance().clearCode();

    if (rawString.empty()) {
        return;
    }

    for (auto i = rawString.begin(); i != rawString.end(); ++i ) {
        MainWindow::getInstance().codeAppendRow(i->second);
    }
}

bool Basic::matchCommand(QString& str) {
    // check if str is a command
    return COMMANDS.count(str);
}

// run the command
void Basic::runCommand(CommandType type) {
    switch(type) {
    case CommandType::RUN:
        MainWindow::getInstance().clickRunButton();
        break;
    case CommandType::LOAD:
        MainWindow::getInstance().clickLoadButton();
        break;
    case CommandType::CLEAR:
        MainWindow::getInstance().clickClearButton();
        break;
    case CommandType::HELP:
        MainWindow::getInstance().clickHelpButton();
        break;
    case CommandType::SAVE:
        MainWindow::getInstance().clickSaveButton();
        break;
    case CommandType::DEBUG:
        MainWindow::getInstance().clickDebugButton();
        break;
    case CommandType::QUIT:
        QApplication::quit();
        break;
    case CommandType::LIST:
        break;
    }
}

bool Basic::matchStmtWithoutLineNumber(QString& str, QString& stmt) {
    if (str.startsWith("PRINT")) {
        stmt = "PRINT";
        return true;
    } else if (str.startsWith("INPUT")) {
        stmt = "INPUT";
        return true;
    } else if (str.startsWith("LET")) {
        stmt = "LET";
        return true;
    }
    return false;
}

void Basic::clearEnvironment() {
    environment.reset();
}
