#include <cmath>

#include "lexer.hpp"

int char_to_digit(const char c) { return c - '0'; }

bool char_is_digit(const char c) {
    return (c - '0' <= '0' - '9') && (c - '0' >= 0);
}

bool char_is_letter(const char c) {
    return (c - 'A' <= 'A' - 'z') && (c - 'A' >= 0);
}

namespace lexer {
void Lexer::reserve(const Word &t) {
    words.insert(std::make_pair(t.lexeme, std::make_shared<Word>(t)));
}

Lexer::Lexer(std::istream &stream_) : stream(stream_) {
    reserve(Word(Token::TRUE, "true"));
    reserve(Word(Token::FALSE, "false"));
}

std::shared_ptr<Token> Lexer::scan() {
    // White-space and comments
    for (;; peek = stream.get()) {
        if (peek == ' ' || peek == '\t') {
            continue;
        } else if (peek == '\n') {
            line++;
        } else if (peek == '/') {
            peek = stream.get();
            if (peek == '/') {
                for (;; peek = stream.get()) {
                    if (peek == '\n') {
                        break;
                    }
                }
            } else if (peek == '*') {
                for (;; peek = stream.get()) {
                    if (peek == '*') {
                        peek = stream.get();
                        if (peek == '/') {
                            break;
                        }
                        stream.unget();
                    }
                }
            } else {
                stream.unget();
                continue;
            }
        } else {
            break;
        }
    }

    // Integers
    if (char_is_digit(peek)) {
        int v = 0;
        do {
            v = 10 * v + char_to_digit(peek);
            peek = stream.get();
        } while (char_is_digit(peek));

        // Float
        if (peek == '.') {
            float fv = v;
            int place = 1;
            peek = stream.get();
            while (char_is_digit(peek)) {
                fv += char_to_digit(peek) * std::pow(10, place);
                peek = stream.get();
                place++;
            }
            return std::make_shared<Float>(fv);
        }

        return std::make_shared<Num>(v);
    }

    // Float
    if (peek == '.') {
        float fv = 0;
        int place = 1;
        peek = stream.get();
        while (char_is_digit(peek)) {
            fv += char_to_digit(peek) * std::pow(10, place);
            peek = stream.get();
            place++;
        }
        return std::make_shared<Float>(fv);
    }

    // ids
    if (char_is_letter(peek)) {
        std::string s;
        do {
            s += peek;
            peek = stream.get();
        } while (char_is_digit(peek) || char_is_letter(peek));
        if (words.contains(s)) {
            return words.at(s);
        }
        auto w = std::make_shared<Word>(Token::ID, s);
        words.insert(std::make_pair(s, w));
        return w;
    }

    // relations
    switch (peek) {
    case '<':
        if (stream.get() == '=') {
            return std::make_shared<Token>(Token::LTEQ);
        }
        stream.unget();
        return std::make_shared<Token>(Token::LT);
    case '=':
        if (stream.get() == '=') {
            return std::make_shared<Token>(Token::EQ);
        }
        stream.unget();
        break;
    case '!':
        if (stream.get() == '=') {
            return std::make_shared<Token>(Token::NEQ);
        }
        stream.unget();
        break;
    case '>':
        if (stream.get() == '=') {
            return std::make_shared<Token>(Token::GTEQ);
        }
        stream.unget();
        return std::make_shared<Token>(Token::GT);
    }

    auto t = std::make_shared<Token>(peek);
    peek = ' ';
    return t;
}
} // namespace lexer
