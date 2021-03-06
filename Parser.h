#ifndef PARSER_H
#define PARSER_H
#include "Stmt.h"
#include "consts.h"
#include "Token.h"
#include "Expr.h"

class Parser {
private:
    // one line of tokens
    shared_ptr<QList<shared_ptr<Token>>> source;

    // pointer to source (iterator)
    QList<shared_ptr<Token>>::iterator current;
    QList<shared_ptr<Token>>::iterator end;

private:
    bool isAtEnd();

    bool match();

    shared_ptr<Token> advance();

    shared_ptr<LetStmt> getLetStmt();

    shared_ptr<PrintStmt> getPrintStmt();

    shared_ptr<InputStmt> getInputStmt();

    shared_ptr<GotoStmt> getGotoStmt();

    shared_ptr<IfStmt> getIfStmt();

    shared_ptr<EndStmt> getEndStmt();

    shared_ptr<Expr> expression();

    shared_ptr<Expr> addition();

    shared_ptr<Expr> mult();

    shared_ptr<Expr> pow();

    shared_ptr<Expr> unary();

    shared_ptr<Expr> number();

public:
    Parser();

    shared_ptr<Stmt> getStmt(shared_ptr<QList<shared_ptr<Token>>> tokens);
};

#endif // PARSER_H
