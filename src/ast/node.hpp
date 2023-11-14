#ifndef node_HPP
#define node_HPP

#include <string>
#include <vector>

#include "statement.hpp"

namespace ast {

    struct Root {
        std::vector<Statement> children;

        void add_child(Statement&& n) {
            children.emplace_back(std::move(n));
        }

        void print(std::ostream& out, const int tabs = 0) const;
    };
}  // namespace ast

#endif  // node_HPP
