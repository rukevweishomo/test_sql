#ifndef sqlengine_lexer_h
#define sqlengine_lexer_h

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum TokenType {
    KEYWORD, IDENTIFIER, OPERATOR, NUMBER, STRING, END
};

struct Token;
class Lexer {
    public:
        Lexer(const std::string& input);
        std::vector<Token> tokenize();
    private:
        std::string input;
        size_t pos;
        Token readIdentifierOrKeyword();
        Token readNumber();
        Token readString();
        Token readOperator();
        bool isOperator(char c);
        bool isKeyword(const std::string& word);
};
#endif 