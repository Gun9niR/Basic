#ifndef PARSER_H
#define PARSER_H
#include "Stmt.h"
#include "consts.h"
#include "Token.h"
#include "Expr.h"

class Parser {
private:
    // one line of tokens
    shared_ptr<QList<TokenPtr>> source;

    // pointer to source (iterator)
    QList<TokenPtr>::iterator current;
    QList<TokenPtr>::iterator end;

private:
    bool isAtEnd();

    bool match(TokenType t);

    TokenPtr advance();

    shared_ptr<PrintStmt> getPrintStmt();

    shared_ptr<LetStmt> getLetStmt();

    shared_ptr<InputStmt> getInputStmt();

    shared_ptr<GotoStmt> getGotoStmt();

    shared_ptr<IfStmt> getIfStmt();

    shared_ptr<EndStmt> getEndStmt();

    ExprPtr expression();

    ExprPtr addition();

    ExprPtr mult();

    ExprPtr pow();

    ExprPtr unary();

    ExprPtr primary();

public:
    Parser();

    StmtPtr getStmt(shared_ptr<QList<TokenPtr>> tokens);
};

#endif // PARSER_H
