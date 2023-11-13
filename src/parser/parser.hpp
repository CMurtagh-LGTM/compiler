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

        auto fail(const std::string& why);
        ast::Statement statement();
        std::unique_ptr<ast::Expression> expr();
        std::unique_ptr<ast::Expression> expr_prime();
        std::unique_ptr<ast::Expression> term();
        std::unique_ptr<ast::Expression> term_prime();
        std::unique_ptr<ast::Expression> factor();

    public:
        Parser(iter begin, iter end);
        std::unique_ptr<ast::Root> parse();
    };
}  // namespace parser

#endif  // parser_Hpp
