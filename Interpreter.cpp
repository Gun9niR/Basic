#include "Interpreter.h"
#include "qdebug.h"
#include "Exception.h"
#include "QEventLoop"
#include "QtConcurrent"
#include "mainwindow.h"

Interpreter::Interpreter(map<LineNum, QString>& rawInstructions, Environment& environment): rawInstructions(rawInstructions), environment(environment)
{ }

// possible exceptions
// DivisionByZero
// JumpSignal
// NoSuchVariable
// EndSignal

void Interpreter::interpret() {
    // scan instructions
    for (auto rawInstructionIter = rawInstructions.begin(); rawInstructionIter != rawInstructions.end(); ++rawInstructionIter) {
        shared_ptr<QList<TokenPtr>> tokenList;
        try {
            tokenList = scanner.getTokens(rawInstructionIter->second);
        } catch (QString errMsg) {
            // get scanning error, but don't print it, just store it with an ERROR token
            tokenList = make_shared<QList<TokenPtr>>();
            tokenList->push_back(make_shared<Token>(TokenType::ERROR, errMsg));
        }

        StmtPtr stmt;
        try {
            stmt = parser.getStmt(tokenList);
        } catch (QString errMsg) {
            stmt = make_shared<ErrorStmt>(errMsg);
        }

        stmt->visualize(rawInstructionIter->first);
        MainWindow::getInstance().statementAppendRow(" ");
        stmts[rawInstructionIter->first] = stmt;
    }

    pc = stmts.begin();

    while (pc != stmts.end()) {
        try {
            pc->second->execute(environment);
        } catch (const JumpSignal& jmp) {
            int jumpDest = jmp.getJumpDest();
            if (!rawInstructions.count(jumpDest)) {
                // no such line, abort program
                MainWindow::getInstance().errorAppendRow(QString::number(pc->first) + ": " + jmp.getMsg());
                return;
            } else {
                // jump
                pc = stmts.find(jumpDest);
                continue;
            }
        } catch (const EndSignal& end) {
            break;
        } catch (const Exception& e) {
            MainWindow::getInstance().errorAppendRow(QString::number(pc->first) + ": " + e.getMsg());
            return;
        }
        ++pc;
    }

    MainWindow::getInstance().errorAppendRow("Program ended successfully!");
    return;
}

void Interpreter::interpret(QString& str, Environment& environment) {
    Scanner scanner;
    Parser parser;

    shared_ptr<QList<TokenPtr>> tokenList;
    StmtPtr stmt;
    try {
        tokenList = scanner.getTokens(str);
        stmt = parser.getStmt(tokenList);
        stmt->execute(environment);
    } catch (QString errMsg) {
        // get scanning error, but don't print it, just store it with an ERROR token
        MainWindow::getInstance().errorAppendRow(errMsg);
    } catch (const Exception& e) {
        MainWindow::getInstance().errorAppendRow(e.getMsg());
        return;
    }
}
