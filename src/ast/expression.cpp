#include "expression.hpp"

namespace ast {

    void ID::print(std::ostream& out) const {
        out << "ID";
    }

    void Constant::print(std::ostream& out) const {
        out << "Constant " << value;
    }

    void Operation::print(std::ostream& out) const {
        out << "Operation ";
        switch (value) {
            case ADD: out << "+"; break;
            case SUBTRACT: out << "-"; break;
            case MULTIPLY: out << "*"; break;
            case DIVIDE: out << "/"; break;
        }
    }

    void Relation::print(std::ostream& out) const {
        out << "Relation";
    }

    void Access::print(std::ostream& out) const {
        out << "Access";
    }

    void Assign::print(std::ostream& out) const {
        out << "Assign";
    }

    void Expression::print(std::ostream& out) const {
        out << "Expression: ";
        std::visit([&out](auto&& args) { args.print(out); }, *this);
    }

}  // namespace ast
