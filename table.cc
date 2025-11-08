#include "table.h"

Table::Table(const std::string& name) : tableName(name) {}

void Table::buildFromUserInput() {
    int numCols;
    std::cout << "Enter number of columns: ";
    std::cin >> numCols;
    std::cin.ignore(); // handle newline

    for (int i = 0; i < numCols; i++) {
        std::string name, type;
        bool nullable, unique;

        std::cout << "Enter name for column " << (i + 1) << ": ";
        std::getline(std::cin, name);

        std::cout << "Enter type for column '" << name << "' (INT/TEXT/DOUBLE): ";
        std::getline(std::cin, type);

        std::cout << "Is column nullable? (1 = yes, 0 = no): ";
        std::cin >> nullable;

        std::cout << "Is column unique? (1 = yes, 0 = no): ";
        std::cin >> unique;
        std::cin.ignore();

        columns.emplace_back(name, type, nullable, unique);
    }
}

void Table::printTableStructure() const {
    std::cout << "\nTable Structure for '" << tableName << "':\n";
    for (const auto& col : columns) {
        std::cout << "- " << col.getName() << " (" << col.getType() << ")";
        if (!col.isNullable()) std::cout << " NOT NULL";
        if (col.isUnique()) std::cout << " UNIQUE";
        std::cout << "\n";
    }
}

void Table::InsertRows() {
    int numRows;
    std::cout << "Enter number of rows to insert: ";
    std::cin >> numRows;
    std::cin.ignore(); // handle newline

    for (int i = 0; i < numRows; i++) {
        Row newRow;
        std::cout << "Inserting row " << (i + 1) << ":\n";
        for (const auto& col : columns) {
            std::string value;
            std::cout << "Enter value for column '" << col.getName() << "': ";
            std::getline(std::cin, value);
            newRow[col.getName()] = value;
        }
        rows.push_back(newRow);
    }
}

void Table::printAllRows() const {
    std::cout << "\nData in Table '" << tableName << "':\n";
    for (const auto& col : columns) {
        std::cout << col.getName() << "\t";
    }
    std::cout << "\n-----------------------------------\n";

    for (const auto& row : rows) {
        for (const auto& col : columns) {
            auto it = row.find(col.getName());
            if (it != row.end()) {
                std::cout << it->second << "\t";
            } else {
                std::cout << "NULL\t";
            }
        }
        std::cout << "\n";
    }
}