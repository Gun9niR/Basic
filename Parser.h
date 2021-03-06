#ifndef PARSER_H
#define PARSER_H
#include "Stmt.h"
#include "consts.h"
#include "Token.h"

class Parser {
private:
    map<int, shared_ptr<QList<Token>>>& tokens;
    map<int, shared_ptr<Stmt>>& stmts;
};

#endif // PARSER_H
