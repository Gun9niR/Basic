#include "Interpreter.h"
#include "qdebug.h"
#include "qapplication.h"
#include "Exception.h"

Interpreter::Interpreter(map<int, StmtPtr>& stmts): stmts(stmts) {
    environment.reset();
}

// possible exceptions
// DivisionByZero
// JumpSignal
// NoSuchVariable
// EndSignal

void Interpreter::interpret() {
    pc = stmts.begin();

    while (pc != stmts.end()) {
        try {
            pc->second->execute(environment);
        } catch (DivisionByZero dbz) {
            // division by zero, abort program
            qDebug() << QString::number(pc->first) + ": " + dbz.getMsg();
            break;
        } catch (JumpSignal jmp) {
            int jumpDest = jmp.getJumpDest();
            if (!stmts.count(jumpDest)) {
                // no such line, abort program
                qDebug() << QString::number(pc->first) + ": " + jmp.getMsg();
                break;
            } else {
                // jump
                pc = stmts.find(jumpDest);
                continue;
            }
        } catch (NoSuchVariable nsv) {
            // no such variable, abort program
            qDebug() << QString::number(pc->first) + ": " + nsv.getMsg();
            break;
        } catch (EndSignal end) {
            qDebug() << end.getMsg();
            break;
        }

        ++pc;
    }
    return;
}
