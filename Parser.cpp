#include "Parser.h"

Parser::Parser(): source(), current(), end() {}

shared_ptr<LetStmt> Parser::getLetStmt() {
    shared_ptr<LetStmt> stmt = make_shared<LetStmt>();
    return stmt;
}

shared_ptr<PrintStmt> Parser::getPrintStmt() {
    shared_ptr<PrintStmt> stmt = make_shared<PrintStmt>();
    return stmt;
}

shared_ptr<InputStmt> Parser::getInputStmt() {
    shared_ptr<InputStmt> stmt = make_shared<InputStmt>();
    return stmt;
}

shared_ptr<GotoStmt> Parser::getGotoStmt() {
    shared_ptr<GotoStmt> stmt = make_shared<GotoStmt>();
    return stmt;
}

shared_ptr<IfStmt> Parser::getIfStmt() {
    shared_ptr<IfStmt> stmt = make_shared<IfStmt>();
    return stmt;
}

shared_ptr<EndStmt> Parser::getEndStmt() {
    shared_ptr<EndStmt> stmt = make_shared<EndStmt>();
    return stmt;
}

ExprPtr Parser::expression() {

}

ExprPtr Parser::addition() {

}

ExprPtr Parser::mult() {

}

ExprPtr Parser::pow() {

}

ExprPtr Parser::unary() {

}

shared_ptr<Expr> Parser::primary() {

}

StmtPtr Parser::getStmt(shared_ptr<QList<TokenPtr>> tokens) {
    source = tokens;
    current = source->begin();
    end = source->end();

    StmtPtr stmt;
    TokenPtr stmtIdentifier = advance();

    switch (stmtIdentifier->type) {
    case TokenType::LET:
        stmt = getLetStmt();
        break;
    case TokenType::PRINT:
        stmt = getPrintStmt();
        break;
    case TokenType::INPUT:
        stmt = getInputStmt();
        break;
    case TokenType::GOTO:
        stmt = getGotoStmt();
        break;
    case TokenType::IF:
        stmt = getIfStmt();
        break;
    case TokenType::END:
        stmt = getEndStmt();
        break;
    default:
        throw QString("Invalid start of statement: " + stmtIdentifier->lexeme);
    }

    return stmt;
}

bool Parser::isAtEnd() {
    return current == end;
}

TokenPtr Parser::advance() {
    ++current;
    return *(current - 1);
}
