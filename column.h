#ifndef sqlengine_column_h
#define sqlengine_column_h

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <variant> // for holding multiple types
using namespace std;

// A variant type to hold multiple SQL-like data types
using ColumnValue = variant<int, double, string>;

class Column {
private:
    string name;
    string type;  // e.g. "INT", "TEXT", "DOUBLE"
    bool nullable;
    bool uniqueConstraint;

    vector<ColumnValue> values; // stores the actual column data

public:
    // Constructor
    Column(const string& name, const string& type, bool nullable = true, bool unique = false);

    // Getters
    string getName() const;
    string getType() const;
    bool isNullable() const;
    bool isUnique() const;

    // Setters
    void setName(const string& newName);
    void setType(const string& newType);

    // Data handling
    bool addValue(const ColumnValue& value); // returns false if violates constraints
    ColumnValue getValue(size_t index) const;
    size_t size() const;

    // Utility
    void print() const;
};

#endif
