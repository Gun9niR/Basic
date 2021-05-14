#include "Interpreter.h"
#include "qdebug.h"
#include "Exception.h"
#include "QEventLoop"
#include "QtConcurrent"
#include "MainWindow.h"

Interpreter::Interpreter(map<LineNum, QString>& rawInstructions, Environment& environment): rawInstructions(rawInstructions), environment(environment)
{ }

void Interpreter::processRawInstruction() {
    // scan and parse instructions
    TextLineNum textLineNum = 0;

    for (auto rawInstructionIter = rawInstructions.begin(); rawInstructionIter != rawInstructions.end(); ++rawInstructionIter, ++textLineNum) {
        shared_ptr<QList<TokenPtr>> tokenList;
        try {
            tokenList = scanner.getTokens(rawInstructionIter->second);
        } catch (QString errMsg) {
            // get scanning error, but don't print it, just store it with an ERROR token
            tokenList = make_shared<QList<TokenPtr>>();
            tokenList->push_back(make_shared<Token>(TokenType::ERROR, errMsg));
            addCodeDisplayHighlight(textLineNum, RED);
        }

        StmtPtr stmt;
        try {
            stmt = parser.getStmt(tokenList);
        } catch (QString errMsg) {
            stmt = make_shared<ErrorStmt>(errMsg);
            addCodeDisplayHighlight(textLineNum, RED);
        }

        stmts[rawInstructionIter->first] = stmt;
    }


}

void Interpreter::displaySyntaxTree() {
    MainWindow& mainWindow = MainWindow::getInstance();

    for (const auto& stmtItr: stmts) {
        stmtItr.second->visualize(stmtItr.first);
        mainWindow.statementAppendRow(" ");
    }
}

void Interpreter::startDebugging() {
    if (rawInstructions.empty()) {
        MainWindow::getInstance().finishDebug();
        return;
    }
    processRawInstruction();
    mapCodeLine2TextLine();
    pc = stmts.begin();
    prepareInterpretOne();
}

void Interpreter::prepareInterpretOne() {
    setCurrentLineColor(GREEN);

    MainWindow::getInstance().clearStatement();
    pc->second->visualize(pc->first);
}

void Interpreter::mapCodeLine2TextLine() {
    TextLineNum textLineNum = 0;
    codeLine2TextLine.clear();
    for (const auto& stmtItr: stmts) {
        codeLine2TextLine[stmtItr.first] = textLineNum++;
    }
}

void Interpreter::interpretAll() {
    if (rawInstructions.empty()) {
        return;
    }
    processRawInstruction();
    mapCodeLine2TextLine();
    displaySyntaxTree();

    pc = stmts.begin();

    if (interpretFromCurrentPc()) {
        MainWindow::getInstance().errorAppendRow("Program ended successfully!");
    }
}

void Interpreter::interpretRest() {
    MainWindow::getInstance().clearStatement();
    removeCurrentLineColor();
    displaySyntaxTree();

    if (interpretFromCurrentPc()) {
        MainWindow::getInstance().errorAppendRow("Program ended successfully!");
    }
}

void Interpreter::debugStep() {
    auto prevPc = pc;
    if (!interpretOne()) {
        showMessage("出错", "该语句有错误");
        MainWindow::getInstance().finishDebug();
        return;
    }
    if (pc == stmts.end()) {
        showMessage("调试结束", "被调试的程序正常结束");
        removeCurrentLineColor();
        MainWindow::getInstance().finishDebug();
        return;
    }
    removeLineColor(prevPc);
    prepareInterpretOne();
}

bool Interpreter::interpretOne() {
    try {
        pc->second->execute(environment);
    } catch (const JumpSignal& jmp) {
        int jumpDest = jmp.getJumpDest();
        if (!rawInstructions.count(jumpDest)) {
            // no such line, abort program
            MainWindow::getInstance().errorAppendRow(QString::number(pc->first) + ": " + jmp.getMsg());
            setCurrentLineColor(RED);
            return false;
        } else {
            // jump
            pc = stmts.find(jumpDest);
            return true;
        }
    } catch (const EndSignal& end) {
        pc = stmts.end();
        return true;
    } catch (const Exception& e) {
        MainWindow::getInstance().errorAppendRow(QString::number(pc->first) + ": " + e.getMsg());
        setCurrentLineColor(RED);
        return false;
    }
    ++pc;
    return true;
}

void Interpreter::interpret(const QString& str, Environment& environment) {
    Scanner scanner;
    Parser parser;

    shared_ptr<QList<TokenPtr>> tokenList;
    StmtPtr stmt;
    try {
        tokenList = scanner.getTokens(str);
        stmt = parser.getStmt(tokenList);
        stmt->execute(environment);
    } catch (QString errMsg) {
        // get scanning or parsing error
        MainWindow::getInstance().errorAppendRow(errMsg);
    } catch (const Exception& e) {
        // get runtime error
        MainWindow::getInstance().errorAppendRow(e.getMsg());
        return;
    }
}

bool Interpreter::interpretFromCurrentPc() {
    while (pc != stmts.end()) {
        if (!interpretOne()) {
            return false;
        }
    }
    return true;
}

void Interpreter::removeLineColor(map<LineNum, StmtPtr>::iterator& pc) {
    removeCodeDisplayHighlight(codeLine2TextLine[pc->first]);
}

void Interpreter::removeCurrentLineColor() {
    removeLineColor(pc);
}

void Interpreter::setCurrentLineColor(const QColor& color) {
    addCodeDisplayHighlight(codeLine2TextLine[pc->first], color);
}

void Interpreter::addCodeDisplayHighlight(TextLineNum textLineNum, const QColor& color) {
    QTextCursor cursor = MainWindow::getInstance().getCodeDisplayerCursor();

    QTextBlockFormat clearFormat;
    QTextBlockFormat newFormat;

    clearFormat.clearBackground();
    newFormat.setBackground(color);
    setCursorY(cursor, textLineNum);

    cursor.setBlockFormat(clearFormat);
    cursor.setBlockFormat(newFormat);
}

void Interpreter::removeCodeDisplayHighlight(TextLineNum textLineNum) {
    QTextCursor cursor = MainWindow::getInstance().getCodeDisplayerCursor();

    QTextBlockFormat format;
    format.clearBackground();
    setCursorY(cursor, textLineNum);
    cursor.setBlockFormat(format);
}
