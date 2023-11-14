#include "expression.hpp"

namespace ast {

    void ID::print(std::ostream& out, const int tabs) const {
        out << "ID";
    }

    void Constant::print(std::ostream& out, const int tabs) const {
        out << std::string(tabs, ' ') << "Constant " << value << std::endl;
    }

    
    Operation::Operation(Type v):value(v){}

    void Operation::print(std::ostream& out, const int tabs) const {
        out << std::string(tabs, ' ') << "Operation ";
        switch (value) {
            case ADD: out << "+"; break;
            case SUBTRACT: out << "-"; break;
            case MULTIPLY: out << "*"; break;
            case DIVIDE: out << "/"; break;
        }
        std::cout << std::endl;

        std::visit([&out, tabs](auto&& args) { args.print(out, tabs + 1); }, *lhs);
        std::visit([&out, tabs](auto&& args) { args.print(out, tabs + 1); }, *rhs);
    }

    void Relation::print(std::ostream& out, const int tabs) const {
        out << "Relation";
    }

    void Access::print(std::ostream& out, const int tabs) const {
        out << "Access";
    }

    void Expression::print(std::ostream& out, const int tabs) const {
        std::visit([&out, tabs](auto&& args) { args.print(out, tabs); }, *this);
    }

}  // namespace ast
