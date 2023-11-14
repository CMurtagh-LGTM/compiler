#include "token.hpp"

#include "utils.hpp"

namespace lexer {

    std::ostream& operator<<(std::ostream& out, const Token::eof) {
        return out << "EOF";
    }

    std::ostream& operator<<(std::ostream& out, const Token::RelationOperator ro) {
        switch (ro) {
            case Token::LT: return out << "<";
            case Token::GT: return out << ">";
            case Token::EQ: return out << "=";
            case Token::LTEQ: return out << "<=";
            case Token::GTEQ: return out << ">=";
            case Token::NEQ: return out << "!=";
        }
        return out;
    }

    std::string Token::to_string() const {
        return std::visit(overloaded{
                              [](int arg) { return std::to_string(arg); },
                              [](float arg) { return std::to_string(arg); },
                              [](bool arg) { return std::string(arg ? "True" : "False"); },
                              [](char arg) { return std::string(1, arg); },
                              [](const std::string& arg) { return arg; },
                              [](RelationOperator arg) { return std::string("TODO"); },
                              [](eof) { return std::string("EOF"); },
                          },
                          value);
    }

    bool Token::operator==(const std::string& rhs) const {
        if (std::holds_alternative<std::string>(value)) {
            return std::get<std::string>(value) == rhs;
        }
        if (std::holds_alternative<char>(value) && rhs.size() == 1) {
            return std::get<char>(value) == rhs[0];
        }

        return false;
    }

    void Token::print(std::ostream& out) const {
        std::visit([&out](auto&& arg) { out << arg; }, value);
    }

    bool Token::is_eof() const {
        return std::holds_alternative<Token::eof>(value);
    }

    bool Token::is_constant() const {
        return std::holds_alternative<int>(value) || std::holds_alternative<float>(value);
    }


    bool Token::is_id() const{
        return std::holds_alternative<std::string>(value);
    }

    Token::Token(const int v) : value(v) {}
    Token::Token(const float v) : value(v) {}
    Token::Token(const bool v) : value(v) {}
    Token::Token(const char v) : value(v) {}
    Token::Token(const std::string& v) : value(v) {}
    Token::Token(const RelationOperator v) : value(v) {}
    Token::Token(const eof v) : value(v) {}

}  // namespace lexer
