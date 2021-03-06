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

    // check if current->type matches
    bool match(const vector<TokenType>&);
    bool match(TokenType);
    void consume(TokenType, const QString&);
    TokenPtr advance();

    shared_ptr<RemStmt> getRemStmt();

    shared_ptr<PrintStmt> getPrintStmt();

    shared_ptr<LetStmt> getLetStmt();

    shared_ptr<InputStmt> getInputStmt();

    shared_ptr<InputsStmt> getInputsStmt();

    shared_ptr<GotoStmt> getGotoStmt();

    shared_ptr<IfStmt> getIfStmt();

    shared_ptr<PrintfStmt> getPrintfStmt();

    shared_ptr<EndStmt> getEndStmt();

    shared_ptr<ErrorStmt> getErrorStmt(QString errorMsg);

    ExprPtr expression();

    ExprPtr addition();

    ExprPtr mult();

    ExprPtr unaryPow();

    ExprPtr pow();

    ExprPtr unary();

    ExprPtr primary();

    void error(QString errMsg);

    void checkEnd();

public:
    Parser();

    StmtPtr getStmt(shared_ptr<QList<TokenPtr>> tokens);
};

#endif // PARSER_H
