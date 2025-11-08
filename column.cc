#include "column.h"

Column::Column(const string& name, const string& type, bool nullable, bool unique)
    : name(name), type(type), nullable(nullable), uniqueConstraint(unique) {}

string Column::getName() const { return name; }
string Column::getType() const { return type; }
bool Column::isNullable() const { return nullable; }
bool Column::isUnique() const { return uniqueConstraint; }

void Column::setName(const string& newName) { name = newName; }
void Column::setType(const string& newType) { type = newType; }

bool Column::addValue(const ColumnValue& value) {
    // Check uniqueness constraint
    if (uniqueConstraint) {
        for (const auto& v : values) {
            if (v == value) return false; // duplicate found
        }
    }
    values.push_back(value);
    return true;
}

ColumnValue Column::getValue(size_t index) const {
    if (index < values.size())
        return values[index];
    throw out_of_range("Invalid index");
}

size_t Column::size() const {
    return values.size();
}

void Column::print() const {
    cout << "Column: " << name << " (" << type << ")\nValues:\n";
    for (const auto& v : values) {
        visit([](auto&& val) { cout << val << "\n"; }, v);
    }
}
