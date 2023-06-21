#ifndef node_HPP
#define node_HPP

#include <concepts>
#include <memory>
#include <string>
#include <typeindex>

namespace ast {

class syntax_error : public std::exception {
    using std::exception::exception;
};

struct Node {};

struct Expression : public Node {
    enum { id, constant, operation, relation, access, assign } type;
    std::string rvalue();
    std::string lvalue();
};

struct Statement : public Node {
    virtual void gen(std::string &) = 0;
};

struct If : public Statement {
    std::unique_ptr<Expression> e;
    std::unique_ptr<Statement> s;
    If(std::unique_ptr<Expression> &&e, std::unique_ptr<Statement> &&s);

    void gen(std::string &);
};

struct For : public Statement {
    std::unique_ptr<Expression> init, test, increment;
    std::unique_ptr<Statement> s;
    For(std::unique_ptr<Expression> &&init, std::unique_ptr<Expression> &&test,
        std::unique_ptr<Expression> &&increment,
        std::unique_ptr<Statement> &&s);

    void gen(std::string &);
};

} // namespace ast

#endif // node_HPP
