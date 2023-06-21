#ifndef env_HPP
#define env_HPP

#include <string>
#include <unordered_map>

namespace symbol {

struct Symbol {};

class Environment {
    std::unordered_map<std::string, Symbol> table;
    Environment *prev;

  public:
    Environment(Environment *prev_);
    void put(const std::string &s, Symbol sym);
    Symbol *get(const std::string &s);
};

} // namespace symbol

#endif // env_HPP
