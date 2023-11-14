#ifndef statement_HPP
#define statement_HPP

#include <memory>
#include <variant>
#include <vector>

#include "expression.hpp"

namespace ast {

    struct Statement;

    struct IF {
        std::unique_ptr<Expression> condition;
        std::vector<Statement> statements;

        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct FOR {

        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Assign {
        std::string id;
        std::unique_ptr<Expression> expression;

        void print(std::ostream& out, const int tabs = 0) const;
    };

    struct Statement : std::variant<IF, FOR, Assign> {
        using variant::variant;

        void print(std::ostream& out, const int tabs = 0) const;
    };

}

#endif // statement_HPP
