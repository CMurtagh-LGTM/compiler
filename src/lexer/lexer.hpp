#ifndef lexer_Hpp
#define lexer_Hpp

#include <unordered_map>
#include <string>
#include <istream>
#include <memory>

#include "token.hpp"

namespace lexer {
    class Lexer {
        int line = 0;
        char peek = ' ';
        std::unordered_map<std::string, std::shared_ptr<Word>> words{};
        std::istream& stream;

        void reserve(const Word& t);
    public:
        Lexer(std::istream& stream_);
        std::shared_ptr<Token> scan();
    };
}

#endif //lexer_Hpp
