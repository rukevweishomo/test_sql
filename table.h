#ifndef sqlengine_table_h
#define sqlengine_table_h

#include <vector>
#include <string>
#include <iostream>
#include "row.h"
#include "column.h"

class Table {
private:
    std::string tableName;
    std::vector<Column> columns;

public:
    Table(const std::string& name = "");

    void buildFromUserInput();
    void printTableStructure() const;

    //To-Do: add other table operations later
};

#endif
