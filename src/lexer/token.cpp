#include "token.hpp"

namespace lexer {
Token::Token(const int t) : tag(t) {}
Num::Num(const int v) : Token(Token::NUM), value(v) {}
Float::Float(const float v) : Token(Token::NUM), value(v) {}
Word::Word(const int t, const std::string &s) : Token(t), lexeme(s) {}

Word::Word(const Word &w) : Token(w.tag), lexeme(w.lexeme) {}
} // namespace lexer
