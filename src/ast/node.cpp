#include "node.hpp"

namespace ast {

    void Node::print(std::ostream& out, const int tabs) const {
        out << std::string(tabs * 2, ' ');
        std::visit([&out](auto&& args) { args.print(out); }, *this);
        out << std::endl;

        for (auto& child : children) {
            child.print(out, tabs + 1);
        }
    }

    void Root::print(std::ostream& out) const {
        out << "Root";
    }

    void Statement::print(std::ostream& out) const {
        out << "S";
    }

}  // namespace ast
