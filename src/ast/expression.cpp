#include "expression.hpp"

namespace ast {


void ID::print(std::ostream& out) const {
    out << "ID";
}

void Constant::print(std::ostream& out) const {
    out << "Constant";
}

void Operation::print(std::ostream& out) const {
    out << "Operation";
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
    std::visit([&out](auto&& args){args.print(out);}, *this);
}

}
