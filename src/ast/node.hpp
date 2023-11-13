#ifndef node_HPP
#define node_HPP

#include <memory>
#include <string>
#include <typeindex>
#include <variant>
#include <vector>

#include "expression.hpp"

namespace ast {

    struct Statement {
        void print(std::ostream& out, const int tabs = 0) const;

        std::unique_ptr<Expression> expression; // TODO
        Statement(std::unique_ptr<Expression>&& expression);
    };

    struct Root {
        std::vector<Statement> children;
        void add_child(Statement&& n) {
            children.emplace_back(std::move(n));
        }

        void print(std::ostream& out, const int tabs = 0) const;
    };
}  // namespace ast

#endif  // node_HPP
