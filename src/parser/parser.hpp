#ifndef parser_Hpp
#define parser_Hpp

#include <memory>
#include <stack>
#include <vector>

#include "ast/node.hpp"
#include "lexer/token.hpp"
#include "syntax_error.hpp"

namespace parser {

    class Parser {
        using iter = std::vector<lexer::Token>::const_iterator;
        iter begin;
        iter curr;
        iter end;

        ast::Node fail(const std::string& why);
        ast::Node expr();
        std::optional<ast::Node> expr_prime();
        ast::Node term();
        std::optional<ast::Node> term_prime();
        ast::Node factor();

    public:
        Parser(iter begin, iter end);
        std::unique_ptr<ast::Node> parse();
    };
}  // namespace parser

#endif  // parser_Hpp
