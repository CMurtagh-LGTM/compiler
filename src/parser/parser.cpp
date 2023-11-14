#include "parser.hpp"

#include <iostream>

#include "ast/expression.hpp"
namespace parser {

    using ast::Root;
    using ast::Statement;
    using ast::Expression;

    Parser::Parser(iter begin_, iter end_) : begin(begin_), curr(begin_), end(end_) {}

    auto Parser::fail(const std::string& why) {
        throw syntax_error(why, *curr, std::distance(begin, curr));
    }

    std::unique_ptr<Root> Parser::parse() {
        auto tree = std::make_unique<Root>();
        while(curr != end){
            tree->add_child(stmnt());
        }
        return tree;
    }

    Statement Parser::stmnt() {
        if(*curr == "if"){
            return branch();
        }
        if(*curr == "for"){
            fail("unimplemented");
        }
        
        if(*curr == "let"){
            return assign();
        }

        fail("Expected a statement");
        return Statement();
    }

    Statement Parser::branch(){
        curr++;

        auto statement = Statement(ast::IF());
        auto& branch = std::get<ast::IF>(statement);

        if(*curr != "("){
            fail("Expected ( to start if condition");
        }
        curr++;

        branch.condition = expr();

        if(*curr != ")"){
            fail("Expected ) to end if condition");
        }
        curr++;

        if(*curr != "{"){
            fail("Expected {");
        }
        curr++;
 
        while(*curr != "}"){
            branch.statements.push_back(Parser::stmnt());
        }
        curr++;

        return statement;
    }

    Statement Parser::assign(){
        curr++;

        auto statement = Statement(ast::Assign());
        auto& assign = std::get<ast::Assign>(statement);

        if(!curr->is_id()){
            fail("Expected ID to assign to");
        }
        assign.id = curr->get<std::string>();
        curr++;

        if(*curr != "="){
            fail("Expected = for assignment");
        }
        curr++;

        assign.expression = expr();

        if(*curr != ";"){
            fail("Expected ; to finish assignment");
        }
        curr++;

        return statement;
    }

    std::unique_ptr<Expression> Parser::expr() {
        auto t = term();
        auto n = expr_prime();
        if (n) {
            std::get<ast::Operation>(*n).lhs = std::move(t);
            return n;
        }
        return t;
    }

    std::unique_ptr<ast::Expression> Parser::expr_prime() {
        if (curr == end || *curr == ";" || (*curr) == ")") {
            return std::unique_ptr<ast::Expression>();
        }

        ast::Operation::Type operation_type;
        if (*curr == "+") {
            operation_type = ast::Operation::ADD;
        }
        else if (*curr == "-") {
            operation_type = ast::Operation::SUBTRACT;
        }
        else {
            fail("Expected * or /");
            return std::unique_ptr<ast::Expression>();
        }

        curr++;
        auto n = std::make_unique<Expression>(ast::Operation(operation_type));
        auto t = term();
        auto e = expr_prime();

        if (e) {
            std::get<ast::Operation>(*e).lhs = std::move(t);
            std::get<ast::Operation>(*n).rhs = std::move(e);
        }
        else {
            std::get<ast::Operation>(*n).rhs = std::move(t);
        }
        return n;
    }

    std::unique_ptr<ast::Expression> Parser::term() {
        auto f = factor();
        auto n = term_prime();
        if (n) {
            std::get<ast::Operation>(*n).lhs = std::move(f);
            return n;
        }
        else {
            return f;
        }
    }

    std::unique_ptr<ast::Expression> Parser::term_prime() {
        if (curr == end || *curr == ";" || (*curr) == "+" || (*curr) == "-" || (*curr) == ")") {
            return std::unique_ptr<ast::Expression>();
        }

        ast::Operation::Type operation_type;
        if ((*curr == "*")) {
            operation_type = ast::Operation::MULTIPLY;
        }
        else if ((*curr == "/")) {
            operation_type = ast::Operation::DIVIDE;
        }
        else {
            fail("Expected * or /");
            return std::unique_ptr<ast::Expression>();
        }

        curr++;
        auto n = std::make_unique<ast::Expression>(ast::Operation(operation_type));
        auto f = factor();
        auto t = term_prime();

        if (t) {
            std::get<ast::Operation>(*t).lhs = std::move(f);
            std::get<ast::Operation>(*n).rhs = std::move(t);
        }
        else {
            std::get<ast::Operation>(*n).rhs = std::move(f);
        }

        return n;
    }

    std::unique_ptr<Expression> Parser::factor() {
        if ((*curr) == "(") {
            curr++;
            auto n = expr();
            if ((*curr) != ")") {
                fail("Expected closing bracket");
                return std::unique_ptr<Expression>();
            }
            curr++;
            return n;
        }
        else if ((*curr).is_constant()) {
            auto n = std::make_unique<ast::Expression>(std::visit(
                [](auto&& arg) -> ast::Constant {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, int>) {
                        return ast::Constant(arg);  // TODO
                    }
                    return ast::Constant();
                },
                curr->get()));
            curr++;
            return n;
        }
        fail("Expected a constant");
        return std::unique_ptr<Expression>();
    }

}  // namespace parser
