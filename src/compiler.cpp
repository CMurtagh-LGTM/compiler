#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include <sstream>
#include <iostream>
#include <variant>

int main(int argc, char *argv[]) {
    std::istringstream in;
    if (argc <= 1){
        std::cout << "Please provide program" << std::endl;
        return 0;
    }
    in = std::istringstream(argv[1]);
    auto lexer = lexer::Lexer(in);
    auto tokens = lexer.scan_all();

    for(auto token : tokens){
        std::cout << *token << ", ";
    }
    std::cout << std::endl;

    auto parser = parser::Parser(tokens.begin(), tokens.end());

    try {
        auto ast_root = parser.parse();
        ast_root->print(std::cout);
    }
    catch (parser::syntax_error& e){
        std::cout << std::endl;
        std::cout << e.what() << std::endl;
    }
}
