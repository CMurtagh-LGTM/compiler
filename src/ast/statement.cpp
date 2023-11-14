#include "statement.hpp"

namespace ast {

    void IF::print(std::ostream& out, const int tabs) const {
        std::cout << std::string(tabs, ' ') << "If" << std::endl;
        condition->print(out, tabs + 1);
        for(auto& statement : statements){
            statement.print(out, tabs + 1);
        }
    }

    void FOR::print(std::ostream& out, const int tabs) const {
        // TODO
    }

    void Assign::print(std::ostream& out, const int tabs) const {
        out << std::string(tabs, ' ') << "Assign " << id << std::endl;
        expression->print(out, tabs + 1);
    }

    void Statement::print(std::ostream& out, const int tabs) const {
        std::visit([&out, tabs](auto&& args) { args.print(out, tabs); }, *this);
    }

}
