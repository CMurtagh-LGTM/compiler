#ifndef expression_HPP
#define expression_HPP

#include <iostream>
#include <variant>

namespace ast {

struct ID {
    void print(std::ostream &out) const;
};

struct Constant {
    int value; // TODO
    void print(std::ostream &out) const;
};

struct Operation {
    enum Type {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
    } value;
    void print(std::ostream &out) const;
};

struct Relation {
    void print(std::ostream &out) const;
};

struct Access {
    void print(std::ostream &out) const;
};

struct Assign {
    void print(std::ostream &out) const;
};

struct Expression
    : std::variant<ID, Constant, Operation, Relation, Access, Assign> {
    using variant::variant;

    void print(std::ostream &out) const;
};

} // namespace ast

#endif // expression_HPP
