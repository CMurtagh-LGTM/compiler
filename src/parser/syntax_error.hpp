#ifndef syntax_error_HPP
#define syntax_error_HPP

#include "lexer//token.hpp"

#include <string>

#include <cpptrace/cpptrace.hpp>

namespace parser {
class syntax_error : public cpptrace::exception_with_message {
    int offset;

  public:
    syntax_error(const std::string &why, const lexer::Token letter,
                 const int offset);

    syntax_error &operator=(const syntax_error &other) noexcept;
};
} // namespace parser

#endif // syntax_error_HPP
