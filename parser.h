#ifndef sqlengine_parser_h
#define sqlengine_parser_h

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include "lexer.h"
using namespace std;

struct Clause;
struct Set_Clause;
struct SelectStatement;
struct InsertStatement;
struct UpdateStatement;
struct DeleteStatement;
class Parser {
    private:
        std::vector<Token> tokens;
        int pos = 0;
        Token peek();
        Token advance();
        void ErrorCommandMessage(string command);
        void ErrorClauseMessage(string clause);
    public:
        Parser(vector<Token> t) : tokens(t) {};
        SelectStatement parseSelect();
        InsertStatement parseInsert();
        UpdateStatement parseUpdate();
        DeleteStatement parseDelete();
};
#endif