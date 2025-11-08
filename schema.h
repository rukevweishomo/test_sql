#include <string>
#include <vector>
#include <unordered_map>

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

    void addColumn(const std::string& name, const std::string& type, bool isPrimaryKey = false, bool isNullable = true);

    const Column* getColumn(const std::string& name) const;

    size_t columnCount() const;

    const std::vector<Column>& getColumns() const;
private:
    std::vector<Column> columns;
    std::unordered_map<std::string, size_t> nameToIndex;
};