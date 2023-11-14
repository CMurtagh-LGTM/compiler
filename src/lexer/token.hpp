#ifndef token_HPP
#define token_HPP

#include <memory>
#include <ostream>
#include <string>
#include <variant>

namespace lexer {

    struct Token {
        struct eof {
            friend std::ostream& operator<<(std::ostream& out, const eof);
        };

        enum RelationOperator {
            LT,
            GT,
            EQ,
            LTEQ,
            GTEQ,
            NEQ,
        };

        Token(const int);
        Token(const float);
        Token(const bool);
        Token(const char);
        Token(const std::string&);
        Token(const RelationOperator);
        Token(const eof);

        bool operator==(const std::string&) const;

        void print(std::ostream& out) const;

        bool is_constant() const;
        bool is_eof() const;
        bool is_id() const;

        std::string to_string() const;

        template <typename T>
        T get() const {
            return std::get<T>(value);
        }

        auto& get() const {
            return value;
        }

    private:
        std::variant<int, float, bool, char, std::string, RelationOperator, eof> value;
    };

    std::ostream& operator<<(std::ostream& out, const Token::RelationOperator);

}  // namespace lexer

#endif  // token_HPP
