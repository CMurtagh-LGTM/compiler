#include "parser.hpp"
#include "ast/expression.hpp"

#include <iostream>
namespace parser {

bool operator==(std::shared_ptr<lexer::Token> lhs, const std::string& rhs){
    return (*lhs) == rhs;
}

Parser::Parser(iter begin_, iter end_):begin(begin_), curr(begin_), end(end_){}

std::unique_ptr<ast::Node> Parser::parse(){
    auto tree = std::make_unique<ast::Node>(ast::Root());
    if(expr(*tree) && curr == end){
        return tree;
    }
    fail("Empty File or Expr");
    return tree;
}

bool Parser::fail(const std::string& why){
    throw syntax_error(why, **curr, std::distance(begin, curr));
}

bool Parser::expr(ast::Node& n){
    auto e = n.add_child<ast::Operation>();
    if(term(e)){
        return expr_prime(e);
    }
    return fail("Expected Term");
}

bool Parser::expr_prime(ast::Node& n){
    if(curr == end){
        return true;
    }
    if((*curr) == "+" || (*curr) == "-"){
        curr++;
        if(term(n)){
            return expr_prime(n);
        }else{
            return fail("Expected Term");
        }
    }else if((*curr) == ")"){
        return true;
    }
    return fail("Expected + or - or )");
}

bool Parser::term(ast::Node& n){
    auto e = n.add_child<ast::Operation>();
    if(factor(e)){
        return term_prime(e);
    }
    return fail("Expected Factor");
}

bool Parser::term_prime(ast::Node& n){
    if(curr == end){
        return true;
    }
    if((*curr) == "x" || (*curr) == "/"){
        curr++;
        if(factor(n)){
            return term_prime(n);
        }
        return fail("z");
    }
    else if((*curr) == "+" || (*curr) == "-" || (*curr) == ")"){
        return true;
    }
    return fail("Expected x or / or + or - or )");
}

bool Parser::factor(ast::Node& n){
    if((*curr) == "("){
        curr++;
        if(!expr(n) || (*curr) != ")"){
            return fail("z");
        }
        curr++;
        return true;
    }
    else if((*curr)->tag == 256 || (*curr)->tag == 257){
        n.add_child<ast::Constant>();
        curr++;
        return true;
    }
    return fail("z");
}

}


