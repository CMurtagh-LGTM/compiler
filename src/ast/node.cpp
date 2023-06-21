#include "node.hpp"

namespace ast {

static int label_count = 0;
static int label() { return label_count++; }

std::string Expression::rvalue() { return ""; }

std::string Expression::lvalue() { return ""; }

If::If(std::unique_ptr<Expression> &&e_, std::unique_ptr<Statement> &&s_)
    : e(std::move(e_)), s(std::move(s_)) {}

void If::gen(std::string &out_stream) {
    std::string n = e->rvalue();
    auto after = std::to_string(label());

    out_stream += "ifFalse " + n + " goto " + after + "\n";
    s->gen(out_stream);
    out_stream += after + ":\n";
}

For::For(std::unique_ptr<Expression> &&init_,
         std::unique_ptr<Expression> &&test_,
         std::unique_ptr<Expression> &&increment_,
         std::unique_ptr<Statement> &&s_)
    : init(std::move(init_)), test(std::move(test_)),
      increment(std::move(increment_)), s(std::move(s_)) {}

void For::gen(std::string &out_stream) {
    std::string n_init = init->rvalue();
    std::string n_test = test->rvalue();
    std::string n_incr = increment->rvalue();
    auto start = std::to_string(label());
    auto after = std::to_string(label());

    out_stream += n_init + "\n";
    out_stream += start + ":\n";
    out_stream += "ifFalse " + n_test + " goto " + after + "\n";
    s->gen(out_stream);
    out_stream += n_incr + "\n";
    out_stream += "goto " + start + "\n";
    out_stream += after + ":\n";
}

} // namespace ast
