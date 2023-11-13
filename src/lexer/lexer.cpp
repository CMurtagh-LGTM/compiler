#include "lexer.hpp"

#include <cmath>

int char_to_digit(const char c) {
    return c - '0';
}

bool char_is_digit(const char c) {
    return c >= '0' && c <= '9';
}

bool char_is_letter(const char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

namespace lexer {
    Lexer::Lexer(std::istream& s) : stream(s) {}

    Token Lexer::scan() {
        // White-space and comments
        peek = stream.get();
        for (;; peek = stream.get()) {
            if (peek == ' ' || peek == '\t') {
                continue;
            }
            else if (peek == '\n') {
                line++;
            }
            else if (peek == '/') {
                peek = stream.get();
                if (peek == '/') {
                    for (;; peek = stream.get()) {
                        if (peek == '\n') {
                            break;
                        }
                    }
                }
                else if (peek == '*') {
                    for (;; peek = stream.get()) {
                        if (peek == '*') {
                            peek = stream.get();
                            if (peek == '/') {
                                break;
                            }
                            stream.unget();
                        }
                    }
                }
                else {
                    stream.unget();
                    peek = '/';
                    break;
                }
            }
            else {
                break;
            }
        }

        // EOF
        if (peek == std::istream::traits_type::eof()) {
            return Token(Token::eof());
        }

        // Integers
        if (char_is_digit(peek)) {
            int v = 0;
            do {
                v    = 10 * v + char_to_digit(peek);
                peek = stream.get();
            } while (char_is_digit(peek));

            // Float
            if (peek == '.') {
                float fv  = v;
                int place = 1;
                peek      = stream.get();
                while (char_is_digit(peek)) {
                    fv += char_to_digit(peek) * std::pow(10, place);
                    peek = stream.get();
                    place++;
                }
                return Token(fv);
            }

            stream.unget();

            return Token(v);
        }

        // Float
        if (peek == '.') {
            float fv  = 0;
            int place = 1;
            peek      = stream.get();
            while (char_is_digit(peek)) {
                fv += char_to_digit(peek) * std::pow(10, place);
                peek = stream.get();
                place++;
            }
            return Token(fv);
        }

        // ids
        if (char_is_letter(peek)) {
            std::string s;
            do {
                s += peek;
                peek = stream.get();
            } while (char_is_digit(peek) || char_is_letter(peek));
            return Token(s);
        }

        // relations
        switch (peek) {
            case '<':
                if (stream.get() == '=') {
                    return Token(Token::LTEQ);
                }
                stream.unget();
                return Token(Token::LT);
            case '=':
                if (stream.get() == '=') {
                    return Token(Token::EQ);
                }
                stream.unget();
                break;
            case '!':
                if (stream.get() == '=') {
                    return Token(Token::NEQ);
                }
                stream.unget();
                break;
            case '>':
                if (stream.get() == '=') {
                    return Token(Token::GTEQ);
                }
                stream.unget();
                return Token(Token::GT);
        }

        auto t = Token(peek);
        peek   = ' ';
        return t;
    }

    std::vector<Token> Lexer::scan_all() {
        std::vector<Token> tokens;
        auto token = scan();
        while (!token.is_eof()) {
            tokens.push_back(token);
            token = scan();
        }
        return tokens;
    }
}  // namespace lexer
