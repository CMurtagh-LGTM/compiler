#ifndef lexer_Hpp
#define lexer_Hpp

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"

namespace lexer {
class Lexer {
    int line = 0;
    char peek = ' ';
    std::istream &stream;

  public:
    Lexer(std::istream &stream_);
    Token scan();
    std::vector<Token> scan_all();
};
} // namespace lexer

#endif // lexer_Hpp
