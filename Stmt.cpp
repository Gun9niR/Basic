#include "Stmt.h"

LetStmt::LetStmt(TokenPtr name, ExprPtr initializer): name(name), initializer(initializer) {}

void LetStmt::execute(Environment& environment) {

}

PrintStmt::PrintStmt(ExprPtr expr): expr(expr) {}

void PrintStmt::execute(Environment& environment) {

}

InputStmt::InputStmt(TokenPtr name): name(name) {}

void InputStmt::execute(Environment& environment) {

}

GotoStmt::GotoStmt(int lineNum): lineNum(lineNum) {}

void GotoStmt::execute(Environment& environment) {

}

IfStmt::IfStmt(TokenPtr op, ExprPtr e1, ExprPtr e2, int lineNum): op(op), expr1(e1), expr2(e2), lineNum(lineNum) {}
void IfStmt::execute(Environment& environment) {

}

EndStmt::EndStmt() {}

void EndStmt::execute(Environment& environment) {

}
