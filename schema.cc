#include "schema.h"

class Schema {
public:
    struct Column {
        std::string name;
        std::string type;
        bool isPrimaryKey;
        bool isNullable;

        Column(const std::string& n, const std::string& t, bool pk = false, bool nullable = true)
            : name(n), type(t), isPrimaryKey(pk), isNullable(nullable) {}
    };

    Schema() = default;

    void addColumn(const std::string& name, const std::string& type, bool isPrimaryKey = false, bool isNullable = true) {
        columns.emplace_back(name, type, isPrimaryKey, isNullable);
        nameToIndex[name] = columns.size() - 1;
    }

    const Column* getColumn(const std::string& name) const {
        auto it = nameToIndex.find(name);
        if (it != nameToIndex.end()) {
            return &columns[it->second];
        }
        return nullptr;
    }

    size_t columnCount() const {
        return columns.size();
    }

    const std::vector<Column>& getColumns() const {
        return columns;
    }

private:
    std::vector<Column> columns;
    std::unordered_map<std::string, size_t> nameToIndex;
};