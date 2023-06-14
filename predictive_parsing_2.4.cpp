#include <string>
#include <iostream>

struct SyntaxError{
    int position;
    std::string message;
    SyntaxError(int p, std::string m) : position(p), message(m) {}
};

void match(const char t, const std::string& input, int& current_terminal){
    if(input[current_terminal] == t){
        current_terminal ++;
    } else {
        throw SyntaxError(current_terminal, "match");
    }
}

void A(const std::string& input, int& current_terminal){
    switch(input[current_terminal]) {
        case '+':
            match('+', input, current_terminal);
            A(input, current_terminal);
            A(input, current_terminal);
            break;
        case 'a':
            match('a',input, current_terminal);
            break;
        default:
            throw SyntaxError(current_terminal, "S");
    }
}

void A(const std::string& input){
    int current_terminal = 0;
    A(input, current_terminal);
}

void B(const std::string& input, int& current_terminal){
    switch(input[current_terminal]) {
        case '(':
            match('(', input, current_terminal);
            B(input, current_terminal);
            match(')', input, current_terminal);
            B(input, current_terminal);
            break;
    }
}

void B(const std::string& input){
    int current_terminal = 0;
    B(input, current_terminal);
}

void C(const std::string& input, int& current_terminal);

void optC(const std::string& input, int& current_terminal){
    if(input[current_terminal] == '0'){
        C(input, current_terminal);
    }
}

void C(const std::string& input, int& current_terminal){
    switch(input[current_terminal]) {
        case '0':
            match('0', input, current_terminal);
            optC(input, current_terminal);
            match('1', input, current_terminal);
            break;
        default:
            throw SyntaxError(current_terminal, "S");
    }
}

void C(const std::string& input){
    int current_terminal = 0;
    C(input, current_terminal);
}

int main(){
    try{
        A("+aa");
        A("++aaa");
        A("++aa+aa");
        B("(()())(())");
        //C(""); should fail
        C("0011");
        std::cout << "correct syntax" << std::endl;
    }catch(SyntaxError& e){
        std::cout << "Syntax error: " << e.position << " " << e.message << std::endl;
    }
}
