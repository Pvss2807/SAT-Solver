#include "tokenizer.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cctype>

Tokenizer::Tokenizer(std::string ln, bool flag)
{
    // complete the constructor
    Tokenizer::token_line = ln;
    Tokenizer::token_index = 0;
    this->token_flag = flag;
    if (this->token_flag)
    {
        formula(this->token_line);
    }
    else
    {
        assignment(this->token_line);
    }
}

bool Tokenizer::advanceToken()
{
    // your code starts here
    if (int(this->token_vector.size()) < this->token_index + 1)
    {
        return false;
    }
    this->token_index++;
    return true;
}
bool Tokenizer::hasToken() const
{
    // your code starts here
    if (int(this->token_vector.size()) < this->token_index + 1)
    {
        return false;
    }
    return true;
}
void Tokenizer::formula(std::string ln)
{   
    std::string operators = "()+-*";
    int i = 0;
    bool foundSpace=false;
    bool foundVar=false;
    while (i < ln.length())
    {
        Token token;
        if(isblank(ln[i])){
            i++;
            continue;
        }
        if (operators.find(ln[i]) != std::string::npos)
        {
            token.content = this->token_line[i];
            token.type = "operator";
            i++;
        }
        else if (isdigit(ln[i]))
        {
            if((ln[i]) == '1' || ln[i] == '0'){
                 if (isalpha(ln[i+1]) && i != (ln.length() - 1))
            {
                throw "Error: invalid input";
            }
            else
            {
                token.content = this->token_line[i];
                token.type = "constant";
                i++;
            }
            }else{
                throw "Error: invalid input";
            }
           
        }
        else
        {   
            std::string dummy = "";
            while (i < int(ln.length()))
            {
                if (operators.find(ln[i]) != std::string::npos)
                {
                    break;
                }
                else if(isblank(ln[i])){
                    foundSpace=true;
                    if(isalnum(ln[i-1]) && isalnum(ln[i+1])){
                        throw "Error: invalid input";
                }
                    i++;
                    continue;
                }
                if(foundVar&&foundSpace){
                    throw "Error: invalid input";
                }
                dummy += ln[i];
                if(foundVar==false && dummy.size()>0){
                    foundVar=true;
                }
                i++;
            }
            if (dummy.length() > 10)
            {
                throw "Error: invalid input";
            }
            token.type = "variable";
            token.content = dummy;
            foundSpace=false;
            foundVar=false;
        }
        this->token_vector.push_back(token);
    }
}

void Tokenizer::assignment(std::string ln)
{
    int i = 0;
    int colon_count=0;
    bool foundSpace=false;
    bool foundVar=false;
    while (i < int(ln.length()))
    {
        Token token;
        if(isblank(ln[i])){
            i++;
            continue;
        }
        else if (isdigit(ln[i]))
        {
            if (ln[i] == '1' || ln[i] == '0'){
                token.type = "constant";
                token.content = ln[i];
                i++;
            }
            else{
                throw "Error: invalid input";
            }
            
        }
        else if (ln[i] == ',')
        {
            i++;
            continue;
        }
        else
        { 
            std::string dummy = "";
            while (i < int(ln.length()))
            {
                if (ln[i] == ':')
                { 
                  colon_count++;
                    i++;
                    break;
                }
                else if(isblank(ln[i])){
                    foundSpace=true;
                    if(isalnum(ln[i-1]) && isalnum(ln[i+1])){
                        throw "Error: invalid input";
                }
                    i++;
                    continue;
                }
                if(foundVar&&foundSpace){
                    throw "Error: invalid input";
                }
                dummy += ln[i];
                if(foundVar==false && dummy.size()>0){
                    foundVar=true;
                }
                i++;
            }
            token.type = "variable";
            token.content = dummy;
            foundSpace=false;
            foundVar=false;
        }
        token_vector.push_back(token);
    }
    if(token_vector.size() != colon_count*2){
      throw "Error: invalid input";
    }
}
// only can be called when hasToken() is true
Token Tokenizer::getToken()
{
    Token resultToken;
    if (hasToken())
        resultToken = this->token_vector[this->token_index];
    return resultToken;
}
