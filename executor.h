#include <memory>
#include <vector>
#include <string>
#include "parser.h"
#include "table.h"

class Executor {
public:
    Executor(std::shared_ptr<Database> db) : db_(db) {}

    // Executes a parsed query and returns results as a vector of rows
    std::vector<Row> execute(const Parser& stmt);

private:
    std::shared_ptr<Database> db_;

    std::vector<Row> executeSelect(const Parser& stmt);

    void executeInsert(const Parser& stmt);

    void executeUpdate(const Parser& stmt);

    void executeDelete(const Parser& stmt);
};