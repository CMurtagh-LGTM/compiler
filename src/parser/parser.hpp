#ifndef parser_Hpp
#define parser_Hpp

#include "ast/node.hpp"
#include "lexer/token.hpp"
#include "syntax_error.hpp"

#include <memory>
#include <stack>
#include <vector>

namespace parser {

class Parser {
    using iter = std::vector<lexer::Token>::const_iterator;
    iter begin;
    iter curr;
    iter end;

    bool fail(const std::string &why);
    bool expr(ast::Node &);
    bool expr_prime(ast::Node &);
    bool term(ast::Node &);
    bool term_prime(ast::Node &);
    bool factor(ast::Node &);

  public:
    Parser(iter begin, iter end);
    std::unique_ptr<ast::Node> parse();
};
} // namespace parser

#endif // parser_Hpp
