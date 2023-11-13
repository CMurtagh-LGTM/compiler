#include "node.hpp"

namespace ast {

    Statement::Statement(std::unique_ptr<Expression>&& expression_):expression(std::move(expression_)){}

    void Root::print(std::ostream& out, const int tabs) const {
        out << "Root" << std::endl;

        for (auto& child : children) {
            child.print(out, tabs + 1);
        }
    }

    void Statement::print(std::ostream& out, const int tabs) const {
        out << std::string(tabs, ' ') << "Satement" << std::endl;
        expression->print(out, tabs+1);
    }

}  // namespace ast
