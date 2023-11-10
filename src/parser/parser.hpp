#ifndef parser_Hpp
#define parser_Hpp

#include "lexer/token.hpp"
#include "ast/node.hpp"
#include "syntax_error.hpp"

#include <stack>
#include <vector>
#include <memory>

namespace parser {

class Parser {
    using iter = std::vector<std::shared_ptr<lexer::Token>>::const_iterator;
    iter begin;
    iter curr;
    iter end;

    bool fail(const std::string& why);
    bool expr(ast::Node&);
    bool expr_prime(ast::Node&);
    bool term(ast::Node&);
    bool term_prime(ast::Node&);
    bool factor(ast::Node&);
public:
    Parser(iter begin, iter end);
    std::unique_ptr<ast::Node> parse();
};
}

#endif // parser_Hpp
