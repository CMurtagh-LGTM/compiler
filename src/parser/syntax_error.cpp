#include "syntax_error.hpp"

#include <format>

namespace parser {

syntax_error::syntax_error(const std::string &why, const lexer::Token token,
                           const int offset_)
    : offset(offset_),
      exception_with_message(std::format("{} tag: {} offset: {}", why,
                                         token.to_string(), offset)) {}

syntax_error &syntax_error::operator=(const syntax_error &other) noexcept {
    offset = other.offset;
    message = other.message;
    return *this;
}

} // namespace parser
