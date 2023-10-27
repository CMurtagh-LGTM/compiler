#ifndef token_HPP
#define token_HPP

#include <ostream>
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
    static constexpr int GT = 62;
    static constexpr int EQ = 260;
    static constexpr int LTEQ = 261;
    static constexpr int GTEQ = 262;
    static constexpr int NEQ = 263;

    static constexpr int START_BLOCK = 123;
    static constexpr int END_BLOCK = 125;

    virtual std::ostream& out(std::ostream& out) const {
        out << tag;
        return out;
    }
};

inline std::ostream& operator<< (std::ostream& out, const Token& t){
    return t.out(out);
}

struct Num : public Token {
    const int value;
    Num(const int v);
    virtual std::ostream& out(std::ostream& out) const {
        out << "Num: " << value;
        return out;
    }
};

struct Float : public Token {
    const float value;
    Float(const float v);
    virtual std::ostream& out(std::ostream& out) const {
        out << "Float: " << value;
        return out;
    }
};

struct Word : public Token {
    const std::string lexeme;
    Word(const int t, const std::string &s);
    Word(const Word &w);
    virtual std::ostream& out(std::ostream& out) const {
        out << "Word: " << lexeme;
        return out;
    }
};
} // namespace lexer

#endif // token_HPP
