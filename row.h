#ifndef ROW_H
#define ROW_H

#include <vector>
#include <string>
#include <variant>

class Row {
public:
    using Value = std::variant<int, double, std::string, std::nullptr_t>;

    Row() = default;
    Row(const std::vector<Value>& values) : values_(values) {}
    void addValue(const Value& value);
    const Value& getValue(size_t index) const;
    size_t size() const;

    // For printing/debugging
    std::string toString() const;

private:
    std::vector<Value> values_;
};

#endif 