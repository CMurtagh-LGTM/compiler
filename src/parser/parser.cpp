#include "parser.hpp"

#include <iostream>

#include "ast/expression.hpp"
namespace parser {

    using ast::Node;

    Parser::Parser(iter begin_, iter end_) : begin(begin_), curr(begin_), end(end_) {}

    std::unique_ptr<Node> Parser::parse() {
        auto tree = std::make_unique<Node>(ast::Root());
        tree->add_child(expr());
        if (curr == end) {
            return tree;
        }
        fail("Tokens left over");
        return tree;
    }

    ast::Node Parser::fail(const std::string& why) {
        throw syntax_error(why, *curr, std::distance(begin, curr));
    }

    ast::Node Parser::expr() {
        auto t = term();
        auto n = expr_prime();
        if (n.has_value()) {
            n->add_child(t);
            return *n;
        }
        return t;
    }

    std::optional<ast::Node> Parser::expr_prime() {
        if (curr == end || (*curr) == ")") {
            return std::optional<Node>();
        }

        ast::Operation::Type operation_type;
        if ((*curr == "+")) {
            operation_type = ast::Operation::ADD;
        }
        else if ((*curr == "/")) {
            operation_type = ast::Operation::SUBTRACT;
        }
        else {
            return fail("Expected * or /");
        }

        curr++;
        auto n = Node(ast::Operation(operation_type));
        auto t = term();
        auto e = expr_prime();

        if (e.has_value()) {
            e->add_child(t);
            n.add_child(*e);
        }
        else {
            n.add_child(t);
        }
        return n;
    }

    ast::Node Parser::term() {
        auto f = factor();
        auto n = term_prime();
        if (n.has_value()) {
            n->add_child(f);
            return *n;
        }
        else {
            return f;
        }
    }

    std::optional<ast::Node> Parser::term_prime() {
        if (curr == end || (*curr) == "+" || (*curr) == "-" || (*curr) == ")") {
            return std::optional<Node>();
        }

        ast::Operation::Type operation_type;
        if ((*curr == "*")) {
            operation_type = ast::Operation::MULTIPLY;
        }
        else if ((*curr == "/")) {
            operation_type = ast::Operation::DIVIDE;
        }
        else {
            return fail("Expected * or /");
        }

        curr++;
        auto n = Node(ast::Operation(operation_type));
        auto f = factor();
        auto t = term_prime();

        if (t.has_value()) {
            t->add_child(f);
            n.add_child(Node(*t));
        }
        else {
            n.add_child(f);
        }

        return n;
    }

    ast::Node Parser::factor() {
        if ((*curr) == "(") {
            curr++;
            auto n = expr();
            if ((*curr) != ")") {
                return fail("Expected closing bracket");
            }
            curr++;
            return n;
        }
        else if ((*curr).is_constant()) {
            auto n = std::visit(
                [](auto&& arg) -> Node {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, int>) {
                        return Node(ast::Constant(arg));  // TODO
                    }
                    return Node(ast::Constant());
                },
                curr->value);
            curr++;
            return n;
        }
        return fail("z");
    }

}  // namespace parser
