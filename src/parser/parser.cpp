#include "parser.hpp"
#include <stdio.h>

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = tokens;
    this->pos = 0;
}

void Parser::unexpectedError() {
    printf("Unexpected token '%s' at %d:%d.\nAborting\n",
            tok2str[this->get().type],
            this->get().line,
            this->get().col);
}

Token Parser::eat(TokType type) {
    if (this->tokens[this->pos].type != type) {
        printf("Expected %s at %d:%d but got %s.\nAborting\n",
               tok2str[type],
               this->tokens[this->pos].line,
               this->tokens[this->pos].col,
               tok2str[this->tokens[this->pos].type]);
        std::exit(1);
    }
    this->pos++;
    return this->tokens[this->pos - 1];
}

Token Parser::get() {
    return this->tokens[this->pos];
}

Token Parser::consume() {
    this->pos++;
    return this->tokens[this->pos - 1];
}

Node Parser::parseVarDecl() {
    this->right = consume();
    this->eat(TokType::semi);
    return Node(this->type, this->left, this->mid, this->right, this->innerNodes);
}

Node Parser::parseFunCall() {
    this->innerNodes.clear();
    eat(TokType::LPar);
    while (this->get().type != TokType::RPar) {
        this->innerNodes.push_back(Node(NodeType::callArg, this->consume()));
    }
    eat(TokType::RPar);
    eat(TokType::semi);
    return Node(this->type, this->left, this->mid, this->right, this->innerNodes);
}

Node Parser::parseDecl() {
    consume();
    this->mid = eat(TokType::name);
    switch (this->get().type) {
        case TokType::eq:
            this->type = NodeType::varDecl;
            this->consume();
            return this->parseVarDecl();
            break;
        default:
            this->unexpectedError();
            std::exit(1);
            break;

    }
}

Node Parser::parseStmt() {
    consume();
    switch (this->get().type) {
        case TokType::LPar:
            this->type = NodeType::funCall;
            return this->parseFunCall();
            break;
        default:
            this->unexpectedError();
            std::exit(1);
            break;
    }
    
}

Node Parser::parseExpr() {
    switch (this->get().type) {
        case TokType::type:
            this->left = get();
            return this->parseDecl();
        case TokType::name:
            this->left = get();
            return this->parseStmt();
        default:
            this->unexpectedError();
            std::exit(1);
            break;
    }
}

void Parser::parse() {
    while (this->pos < this->tokens.size()) {
        this->ast.push_back(this->parseExpr());
    }
}