#include "executor.h"
#include "parser.h"
#include "table.h"

class Executor {
public:
    Executor(std::shared_ptr<Database> db) : db_(db) {}

    // Executes a parsed query and returns results as a vector of rows
    std::vector<Row> execute(const Parser& stmt) {
        switch (stmt().type) {
            case QueryType::SELECT:
                return executeSelect(stmt);
            case QueryType::INSERT:
                executeInsert(stmt);
                return {};
            case QueryType::UPDATE:
                executeUpdate(stmt);
                return {};
            case QueryType::DELETE:
                executeDelete(stmt);
                return {};
            default:
                throw std::runtime_error("Unsupported query type");
        }
    }

private:
    std::shared_ptr<Database> db_;

    std::vector<Row> executeSelect(const Parser& stmt) {
        auto table = db_->getTable(stmt.table());
        return table->select(stmt.columns(), stmt.whereClause());
    }

    void executeInsert(const Parser& stmt) {
        auto table = db_->getTable(stmt.table());
        table->insert(stmt.columns(), stmt.values());
    }

    void executeUpdate(const Parser& stmt) {
        auto table = db_->getTable(stmt.table());
        table->update(stmt.updateFields(), stmt.whereClause());
    }

    void executeDelete(const Parser& stmt) {
        auto table = db_->getTable(stmt.table());
        table->remove(stmt.whereClause());
    }
};