#include "Parser.h"

Parser::Parser(): source(), current(), end() {}

shared_ptr<Stmt> Parser::getStmt(shared_ptr<QList<shared_ptr<Token>>> tokens) {
    source = tokens;
    current = source->begin();
    end = source->end();

    shared_ptr<Stmt> stmt;
    auto stmtIdentifier = advance();

//    switch (stmtIdentifier->type) {

//    default:
//        throw QString("Invalid start of statement");
//    }
    return stmt;
}

bool Parser::isAtEnd() {
    return current == end;
}

shared_ptr<Token> Parser::advance() {
    ++current;
    return *(current - 1);
}
