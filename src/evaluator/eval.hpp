#pragma once

#include <stdint.h>
#include "../parser/parser.hpp"
#include "../lexer/lexer.hpp"

#include <vector>
#include <map>
#include <string>

class Eval {
    public:
        std::map<std::string, std::string> strings;
        std::map<std::string, int> ints;

        std::map<std::string, std::string> varTypes;

        std::map<std::string, std::vector<Node>> functions;
        // std::map<std::string, std::vector<Node>> localvars;

        std::vector<Node> ast;

        Node node;

        //inline Eval(){}

        Token getArg(int pos);

        void evalVarDecl();
        void evalFunDecl();
        void evalFunCall();

        void eval(std::vector<Node> ast);
};