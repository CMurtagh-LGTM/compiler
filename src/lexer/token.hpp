#ifndef token_HPP
#define token_HPP

#include <string>

namespace lexer {
    struct Token {
        const int tag;
        Token(const int t);
        static constexpr int NUM = 256;
        static constexpr int ID = 257;
        static constexpr int TRUE = 258;
        static constexpr int FALSE = 259;

        static constexpr int LT = 60;
        static constexpr int EQ = 61;
        static constexpr int GT = 62;
        static constexpr int LTEQ = 260;
        static constexpr int GTEQ = 261;
        static constexpr int NEQ = 262;
    };

    struct Num : public Token {
        const int value;
        Num(const int v);
    };

    struct Float : public Token {
        const float value;
        Float(const float v);
    };

    struct Word : public Token {
        const std::string lexeme;
        Word(const int t, const std::string& s);
        Word(const Word& w);
    };
}

#endif // token_HPP
