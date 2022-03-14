#include "Exception.h"
#include "Parser.h"

Parser::Parser(): source(), current(), end() {}

shared_ptr<RemStmt> Parser::getRemStmt() {
    TokenPtr comment;

    if (match(TokenType::COMMENT)) {
        comment = advance();
    } else {
        error("Unknown comment error");
    }

    checkEnd();

    return make_shared<RemStmt>(comment);
}

shared_ptr<LetStmt> Parser::getLetStmt() {
    TokenPtr name;

    // get the identifier
    if (match(TokenType::IDENTIFIER)) {
        name = advance();
    } else {
        error("Expect variable name");
    }

    // get '='
    consume(TokenType::EQUAL, "Expect assignment symbol '='");

    // get expression
    ExprPtr initializer = expression();

    checkEnd();

    return make_shared<LetStmt>(name, initializer);
}

shared_ptr<PrintStmt> Parser::getPrintStmt() {
    ExprPtr expr = expression();

    checkEnd();

    return make_shared<PrintStmt>(expr);
}

shared_ptr<InputStmt> Parser::getInputStmt() {
    TokenPtr name;

    if (match(TokenType::IDENTIFIER)) {
        name = advance();
    } else {
        error("Expect variable name");
    }

    checkEnd();

    return make_shared<InputStmt>(name);
}

shared_ptr<InputsStmt> Parser::getInputsStmt() {
    TokenPtr name;

    if (match(TokenType::IDENTIFIER)) {
        name = advance();
    } else {
        error("Expect variable name");
    }

    checkEnd();

    return make_shared<InputsStmt>(name);
}

shared_ptr<GotoStmt> Parser::getGotoStmt() {
    int lineNum;
    if (match(TokenType::NUMBER)) {
        lineNum = static_cast<int>(advance()->value.getIntVal());
    } else {
        error("Expect line number");
    }

    checkEnd();

    return make_shared<GotoStmt>(lineNum);
}

shared_ptr<IfStmt> Parser::getIfStmt() {
    TokenPtr op;
    ExprPtr expr1;
    ExprPtr expr2;
    int lineNum;

    expr1 = expression();

    if (match({TokenType::LESS, TokenType::GREATER, TokenType::EQUAL})) {
        op = advance();
    } else {
        error("Expect comparator in IF condition");
    }

    expr2 = expression();

    consume(TokenType::THEN, "IF requires a THEN");

    if (match(TokenType::NUMBER)) {
        lineNum = static_cast<int>(advance()->value.getIntVal());
    }

    checkEnd();

    return make_shared<IfStmt>(op, expr1, expr2, lineNum);
}

shared_ptr<PrintfStmt> Parser::getPrintfStmt() {
    TokenPtr format;
    vector<ExprPtr> params;

    if (match(TokenType::STRING)) {
        format = advance();
    } else {
        error("Expect format string");
    }

    while (match(TokenType::COMMA)) {
        advance();
        params.emplace_back(expression());
    }

    checkEnd();

    return make_shared<PrintfStmt>(format, params);
}

shared_ptr<EndStmt> Parser::getEndStmt() {
    checkEnd();
    return make_shared<EndStmt>();
}

shared_ptr<ErrorStmt> Parser::getErrorStmt(QString errorMsg) {
    return make_shared<ErrorStmt>(errorMsg);
}

ExprPtr Parser::expression() {
    return addition();
}

ExprPtr Parser::addition() {
    ExprPtr expr = mult();

    while (match({TokenType::PLUS, TokenType::MINUS})) {
        TokenPtr op = advance();
        ExprPtr right = mult();
        expr = make_shared<CompoundExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::mult() {
    ExprPtr expr = unaryPow();

    while (match({TokenType::STAR, TokenType::SLASH})) {
        TokenPtr op = advance();
        ExprPtr right = pow();
        expr = make_shared<CompoundExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::unaryPow() {
    if (match(TokenType::MINUS)) {
        TokenPtr op = advance();
        ExprPtr right = unaryPow();
        return make_shared<CompoundExpr>(op, nullptr, right);
    }

    return pow();
}

ExprPtr Parser::pow() {
    ExprPtr expr = unary();

    if (match(TokenType::POWER)) {
        TokenPtr op = advance();
        ExprPtr right = pow();
        expr = make_shared<CompoundExpr>(op, expr, right);
    }

    return expr;
}

ExprPtr Parser::unary() {
    if (match(TokenType::MINUS)) {
        TokenPtr op = advance();
        ExprPtr right = unary();
        return make_shared<CompoundExpr>(op, nullptr, right);
    }
    return primary();
}

shared_ptr<Expr> Parser::primary() {
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return make_shared<ConstantExpr>(advance()->value);
    }
    if (match(TokenType::IDENTIFIER)) {
        return make_shared<IdentifierExpr>(advance()->lexeme);
    }
    if (match(TokenType::LEFT_PAREN)) {
        advance();
        ExprPtr expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expect ) after expression");
        return expr;
    }

    throw QString("Expect expression");
}

bool Parser::match(TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return type == (*current)->type;
}

bool Parser::match(const vector<TokenType>& types) {
    if (isAtEnd()) {
        return false;
    }
    TokenType currentType = (*current)->type;
    for (auto type: types) {
        if (type == currentType) {
            return true;
        }
    }

    return false;
}

StmtPtr Parser::getStmt(shared_ptr<QList<TokenPtr>> tokens) {
    source = tokens;
    current = source->begin();
    end = source->end();

    StmtPtr stmt;
    TokenPtr stmtIdentifier = advance();

    switch (stmtIdentifier->type) {
    case TokenType::REM:
        stmt = getRemStmt();
        break;
    case TokenType::LET:
        stmt = getLetStmt();
        break;
    case TokenType::PRINT:
        stmt = getPrintStmt();
        break;
    case TokenType::INPUT:
        stmt = getInputStmt();
        break;
    case TokenType::INPUTS:
        stmt = getInputsStmt();
        break;
    case TokenType::GOTO:
        stmt = getGotoStmt();
        break;
    case TokenType::IF:
        stmt = getIfStmt();
        break;
    case TokenType::PRINTF:
        stmt = getPrintfStmt();
        break;
    case TokenType::END:
        stmt = getEndStmt();
        break;
    case TokenType::ERROR:
        throw QString(stmtIdentifier->lexeme);
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

void Parser::error(QString errMsg) {
    throw QString(errMsg);
}

void Parser::consume(TokenType type, const QString& errMsg) {
    if (match(type)) {
        ++current;
    } else {
        throw errMsg;
    }
}

void Parser::checkEnd() {
    if (!isAtEnd()) {
        QString errMsg = "Excessive symbols at the end of the line: ";
        while (!isAtEnd()) {
            errMsg += "<" + advance()->lexeme + "> ";
        }
        throw errMsg;
    }
}
