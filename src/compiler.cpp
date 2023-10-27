#include "lexer/lexer.hpp"
#include <sstream>
#include <iostream>

int main(int argc, char *argv[]) {
    std::istringstream in;
    if (argc <= 1){
        std::cout << "Please provide program" << std::endl;
        return 0;
    }
    in = std::istringstream(argv[1]);
    auto lexer = lexer::Lexer(in);
    auto token = lexer.scan();
    while(token->tag != std::istringstream::traits_type::eof()){
        std::cout << *token << std::endl;
        token = lexer.scan();
    }
}
