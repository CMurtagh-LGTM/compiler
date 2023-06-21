#include "environment.hpp"

namespace symbol {
Environment::Environment(Environment *prev_) : table(), prev(prev_) {}

void Environment::put(const std::string &s, Symbol sym) {
    table.insert(std::make_pair(s, sym));
}

Symbol *Environment::get(const std::string &s) {
    for (Environment *e = this; e != nullptr; e = e->prev) {
        if (e->table.contains(s)) {
            return &(e->table.at(s));
        }
    }
    return nullptr;
}
} // namespace symbol
