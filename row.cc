#include "row.h"

class Row {
public:
    using Value = std::variant<int, double, std::string, std::nullptr_t>;

    Row() = default;
    Row(const std::vector<Value>& values) : values_(values) {}

    void addValue(const Value& value) {
        values_.push_back(value);
    }

    const Value& getValue(size_t index) const {
        return values_.at(index);
    }

    size_t size() const {
        return values_.size();
    }

    // For printing/debugging
    std::string toString() const {
        std::string result;
        for (const auto& val : values_) {
            if (std::holds_alternative<int>(val))
                result += std::to_string(std::get<int>(val));
            else if (std::holds_alternative<double>(val))
                result += std::to_string(std::get<double>(val));
            else if (std::holds_alternative<std::string>(val))
                result += std::get<std::string>(val);
            else
                result += "NULL";
            result += " | ";
        }
        if (!result.empty()) result.pop_back(), result.pop_back(), result.pop_back();
        return result;
    }

private:
    std::vector<Value> values_;
};