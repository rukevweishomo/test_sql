#include "parser.h"


struct Clause {
    string column;
    string op;
    string value;
};
struct Set_Clause {
    vector<string> columns;
    string op;
    vector<string> values;
};

struct SelectStatement {
    vector<string> columns;
    string table;
    Clause where;
};

struct InsertStatement {
    vector<string> columns;
    string table;
    vector<string> values;
};

struct UpdateStatement {
    string table;
    Set_Clause set;
    Clause where;
};

struct DeleteStatement {
    vector<string> columns;
    string table;
    Clause where;
};

Token peek() { return tokens[pos]; }

Token advance() { return tokens[pos++]; }

void ErrorCommandMessage(string command) {
    if (advance().type != TokenType::KEYWORD) {
        throw runtime_error("Expected KEYWORD!");
    } else if (advance().type == TokenType::KEYWORD && advance().value != command) {
        throw runtime_error("Expected " + command + "!");
    } else if (advance().type == TokenType::KEYWORD && advance().value == command) {
        return;
    }
};

void ErrorClauseMessage(string Clause) {
    if (peek().type != TokenType::KEYWORD) {
        throw runtime_error("Expected KEYWORD!");
    } else if (peek().type == TokenType::KEYWORD && peek().value != Clause) {
        throw runtime_error("Expected " + Clause + "!");
    } else if (peek().type == TokenType::KEYWORD && peek().value == Clause) {
        return;
    }
};

Parser::Parser(vector<Token> t) : tokens(t) {} 

SelectStatement parseSelect() {
    SelectStatement stmt;
    Parser::ErrorCommandMessage("SELECT");
    while (true) {
        Token tok = advance();
        if (tok.type == TokenType::IDENTIFIER) {
            stmt.columns.push_back(tok.value);
        } else if (tok.type == TokenType::OPERATOR && tok.value == ',') {
            advance();
        } else if (tok.type == TokenType::KEYWORD && tok.value == "FROM") {
            break;
        }
    }
    Parser::ErrorClauseMessage("FROM");
    stmt.table = advance().value;
    if (tok.type == TokenType::OPERATOR && tok.value == ';') {
        return stmt;
    }
    Parser::ErrorClauseMessage("WHERE");
    advance();
    stmt.where.column = advance().value;
    stmt.where.op = advance().value;
    stmt.where.value = advance().value;
    if (peek().type == TokenType::OPERATOR && peek().value == ';') {
        advance();
        return stmt;
    }
};

UpdateStatement parseUpdate() {
    UpdateStatement stmt;
    Parser::ErrorCommandMessage("UPDATE");
    stmt.table = advance().value;
    Parser::ErrorCommandMessage("SET"); //Potential for loop implementation?
    while (true) {
        Token tok = advance();
        if (tok.type == TokenType::IDENTIFIER) {
            stmt.set.columns.push_back(tok.value);
        } else if (tok.type == TokenType::OPERATOR && tok.value == ',') {
            advance();
        } else if (tok.type == TokenType::OPERATOR && tok.value == '=') {
            stmt.set.op = "=";
            stmt.set.values.push_back(advance().value);
        } else if (tok.type == TokenType::KEYWORD && tok.value == "WHERE") {
            break;
        }
    }
    Parser::ErrorClauseMessage("WHERE");
    advance();
    stmt.where.column = advance().value;
    stmt.where.op = advance().value;
    stmt.where.value = advance().value;
    if (peek().type == TokenType::OPERATOR && peek().value == ';') {
        advance();
        return stmt;
    }
};

InsertStatement parseInsert() {
    InsertStatement stmt;
    Parser::ErrorCommandMessage("INSERT");
    Parser::ErrorClauseMessage("INTO");
    stmt.table = advance().value;
    while (true) {
        Token tok = advance();
        if (tok.type == TokenType::OPERATOR && tok.value == '(') {
            advance();
        } else if (tok.type == TokenType::IDENTIFIER) {
            stmt.columns.push_back(tok.value);
        } else if (tok.type == TokenType::OPERATOR && tok.value == ',') {
            advance();
        } else if (tok.type == TokenType::KEYWORD && tok.value == ')') {
            advance();
            break;
        }
    }
    Parser::ErrorClauseMessage("VALUES");
    while (true) {
        Token tok = advance();
        if (tok.type == TokenType::OPERATOR && tok.value == '(') {
            advance();
        } else if (tok.type == TokenType::IDENTIFIER) {
            stmt.values.push_back(tok.value);
        } else if (tok.type == TokenType::OPERATOR && tok.value == ',') {
            advance();
        } else if (tok.type == TokenType::KEYWORD && tok.value == ")") {
            advance();
            break;
        }
    }
    if (peek().type == TokenType::OPERATOR && peek().value == ';') {
        advance();
        return stmt;
    }
};

DeleteStatement parseDelete() {
    Parser::ErrorCommandMessage("DELETE");
    Parser::ErrorClauseMessage("FROM");
    stmt.table = advance().value;
    Parser::ErrorClauseMessage("WHERE");
    stmt.where.column = advance().value;
    stmt.where.op = advance().value;
    stmt.where.value = advance().value;
    if (peek().type == TokenType::OPERATOR && peek().value == ';') {
        advance();
        return stmt;
    }
};

//Statement Structs: SELECT!!, INSERT!!, UPDATE!!, DELETE!!
//Clause Keywords: FROM!!, WHERE!!, INTO!!, UNION, INTERSECT, SET!!

//To-Do List
// - Implement INSERT statement parsing [Thur] [Done]
// - Implement UPDATE statement parsing [Wed] [Done]
// - Implement SET statement parsing [Wed, inside UPDATE statement] [Done]
// - Implement DELETE statement parsing [Thur] [Done]
//DRY - Find a way to stop repeating yourself [Write error programs to use in AST classes] [Done]
//Write tester for lexer and parser [Fri]
//Test lexer and parser and debug any kinks [Fri/Sat]