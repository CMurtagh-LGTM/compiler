#include "node.hpp"

namespace ast {


    void Root::print(std::ostream& out, const int tabs) const {
        out << "Root" << std::endl;

        for (auto& child : children) {
            child.print(out, tabs + 1);
        }
    }

}  // namespace ast
