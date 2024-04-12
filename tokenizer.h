#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
struct Token
{
    std::string content;
    std::string type;
};
// a tokenzier breaks a stream of string into tokens
class Tokenizer
{
    // your code starts here
    std::string token_line;
    int token_index = 0;
    std::vector<Token> token_vector;
    bool token_flag;

public:
    Tokenizer(std::string ln, bool flag);
    bool advanceToken();   // advance to the next token; return false if no more token exist
    bool hasToken() const; // check whether there is a current token
    Token getToken();      // returns the token being processed
    void formula(std::string ln);
    void assignment(std::string ln);
};

#endif
