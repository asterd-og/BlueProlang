#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "evaluator/eval.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: no input files.\n");
        std::exit(1);
    }
    
    std::ifstream file(argv[1]);

    std::stringstream buffer;
    buffer << file.rdbuf();

    printf("%s\n", buffer.str().c_str());

    Lexer lexer(buffer.str());

    std::vector<Token> toks = lexer.lex();
    /*for (auto tok : toks) {
        printf("%s - %s\n", tok.value.c_str(), tok2str[tok.type]);
    }*/

    Parser parser(toks);
    parser.parse();

    /*printf("\nNODES:\n\n");

    for (auto node : parser.ast) {
        if (node.type == NodeType::varDecl) {
            printf("VarDecl: %s %s = %s\n",
                   node.left.value.c_str(),
                   node.mid.value.c_str(),
                   node.right.value.c_str());
        } else if (node.type == NodeType::funCall) {
            printf("FunCall: %s\nArgs:\n", node.left.value.c_str());
            for (auto inode : node.innerNodes) {
                printf("%s - %s\n", inode.left.value.c_str(),
                       tok2str[inode.left.type]);
            }
        }
    }

    printf("\n\n\n");*/

    Eval evaluator;
    evaluator.eval(parser.ast);
}