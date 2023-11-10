#ifndef node_HPP
#define node_HPP

#include "expression.hpp"

#include <memory>
#include <string>
#include <typeindex>
#include <variant>
#include <vector>

namespace ast {

struct Root {
    void print(std::ostream &out) const;
};

struct Statement {
    void print(std::ostream &out) const;
    // virtual void gen(std::string &) = 0;
};

struct Node : std::variant<Root, Expression, Statement> {
    using variant::variant;

    std::vector<Node> children;

    void print(std::ostream &out, int tabs = 0) const;

    template <typename T, typename... Args> Node &add_child(Args... args) {
        children.push_back(T(args...));
        return children.back();
    }
};

} // namespace ast

#endif // node_HPP
