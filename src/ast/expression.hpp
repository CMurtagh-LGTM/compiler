#ifndef expression_HPP
#define expression_HPP

#include <iostream>
#include <memory>
#include <variant>

namespace ast {

    struct Expression;

    struct ID {
        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Constant {
        int value;  // TODO
        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Operation {
        std::unique_ptr<Expression> lhs;
        std::unique_ptr<Expression> rhs;

        enum Type {
            ADD,
            SUBTRACT,
            MULTIPLY,
            DIVIDE,
        } value;

        Operation(Type v);

        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Relation {
        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Access {
        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Assign {
        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Expression : std::variant<ID, Constant, Operation, Relation> {
        using variant::variant;

        void print(std::ostream& out, const int tabs = 0) const;
    };

}  // namespace ast

#endif  // expression_HPP
