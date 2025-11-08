#include <iostream>
#include <vector>
#include <string>
#include "column.h"
#include "table.h"
#include "lexer.h"
#include "parser.h"

int main() {
    std::string tableName;
    std::cout << "Welcome to the SQL Engine!\n";
    std::cout << "Enter table name: ";
    std::getline(std::cin, tableName);

    Table table(tableName);
    table.buildFromUserInput();
    table.printTableStructure();

    return 0;
}
