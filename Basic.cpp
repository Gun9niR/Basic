#include "Basic.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

Basic::~Basic() { }

Basic::Basic() { }

Basic& Basic::getInstance() {
    static Basic basic;
    return basic;
}

void Basic::interpret() {
    MainWindow::getInstance().disableInput();

    interpreter = make_shared<Interpreter>(stmts);
    interpreter->interpret();

    MainWindow::getInstance().enableInput();
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
        handleRawInstruction(str);
    }

    file.close();
}

int Basic::getLineNumber(QString& str) {
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

void Basic::handleRawInstruction(QString& str) {
    if (str.isEmpty()) {
        return;
    }

    // save a copy of str for error message
    QStringRef copy = &str;

    // check if str is a command
    if (matchCommand(str)) {
        display();
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
    stmts[codeLineNum] = stmt;

    // display code string and syntax tree
    display();
}

void Basic::reset() {
    // reset all properties
    rawInstruction.clear();
    tokens.clear();
    stmts.clear();

    // close the file
    if (file.isOpen()) {
        file.close();
    }
    file.setFileName("");
}


void Basic::displayCode() {
    // clear codeDisplay first
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

bool Basic::matchCommand(QString& str) {
    // check if str is a command
    return COMMANDS.count(str);
}

// run the command
void Basic::runCommand(CommandType type) {
    switch(type) {
    case CommandType::RUN:
        MainWindow::getInstance().clearResult();
        interpret();
        break;
    case CommandType::LOAD:
        MainWindow::getInstance().clickLoadButton();
        break;
    case CommandType::CLEAR:
        MainWindow::getInstance().clickClearButton();
        break;
    case CommandType::HELP:
        QMessageBox::information(NULL, "Help", "Help information",
                                 QMessageBox::Yes);
        break;
    case CommandType::QUIT:
        QApplication::quit();
        break;
    }
}

void Basic::showTokens() {
    for (auto line = tokens.begin(); line != tokens.end(); ++line) {
        auto lineNum = line->first;
        qDebug() << "On line " << lineNum;
        auto list = *(line->second);
        for (auto token = list.begin(); token != list.end(); ++token) {
            qDebug() << **token;
        }
    }
}

int Basic::getDigits(int x) {
    int ret = 0;

    while (x) {
        ++ret;
        x /= 10;
    }

    return ret;
}

void Basic::display() {
    MainWindow::getInstance().clearDisplays();
    displaySyntaxTree();
    displayCode();
}

void Basic::displaySyntaxTree() {
    for (auto iterator: stmts) {
        iterator.second->visualize(iterator.first);
    }
}
