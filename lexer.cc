#include "lexer.h"

struct Token {
    TokenType type;
    std::string value;
};

Lexer::Lexer(const std::string& input) : input(input), pos(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < input.size()) {
        if (isspace(input[pos])) {
            ++pos;
        } else if (isalpha(input[pos])) {
            tokens.push_back(readIdentifierOrKeyword());
        } else if (isdigit(input[pos])) {
            tokens.push_back(readNumber());
        } else if (input[pos] == '\'') {
            tokens.push_back(readString());
        } else if (isOperator(input[pos])) {
            tokens.push_back(readOperator());
        } else {
            ++pos; // skip unknown character
        }
    }
    tokens.push_back({END, ""});
    return tokens;
}

Token Lexer::readIdentifierOrKeyword() {
    size_t start = pos;
    while (pos < input.size() && (isalnum(input[pos]) || input[pos] == '_')) ++pos;
    std::string word = input.substr(start, pos - start);
    if (isKeyword(word)) return {KEYWORD, word};
    return {IDENTIFIER, word};
}

Token Lexer::readNumber() {
    size_t start = pos;
    while (pos < input.size() && isdigit(input[pos])) ++pos;
    return {NUMBER, input.substr(start, pos - start)};
}

Token Lexer::readString() {
    ++pos; // skip opening quote
    size_t start = pos;
    while (pos < input.size() && input[pos] != '\'') ++pos;
    std::string str = input.substr(start, pos - start);
    ++pos; // skip closing quote
    return {STRING, str};
}

Token Lexer::readOperator() {
    char op = input[pos++];
    return {OPERATOR, std::string(1, op)};
}

bool Lexer::isOperator(char c) {
    return c == '=' || c == '<' || c == '>' || c == ',' || c == ';' || c == '(' || c == ')' || c == '\n';
}

bool Lexer::isKeyword(const std::string& word) {
    static const std::vector<std::string> keywords = {
        "SELECT", "FROM", "WHERE", "INSERT", "INTO", "VALUES", "UPDATE", "SET", "DELETE", "UNION", "INTERSECT"
    };
    for (const auto& kw : keywords)
        if (word == kw) return true;
    return false;
}

