#ifndef lexer_Hpp
#define lexer_Hpp

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>

#include "token.hpp"

namespace lexer {
class Lexer {
    int line = 0;
    char peek = ' ';
    std::unordered_map<std::string, std::shared_ptr<Word>> words{};
    std::istream &stream;

    void reserve(const Word &t);

  public:
    Lexer(std::istream &stream_);
    std::shared_ptr<Token> scan();
};
} // namespace lexer

#endif // lexer_Hpp
