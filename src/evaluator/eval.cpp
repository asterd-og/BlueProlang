#include "eval.hpp"
#include <stdio.h>

std::string replaceSeq(const std::string& input,
                       const std::string& toReplace,
                       const std::string& replaceWith) {
    std::string transformedString = input;

    // Loop through the string and replace "\n" with the actual newline character
    for (size_t pos = 0; (pos = transformedString.find(toReplace, pos)) != std::string::npos; pos += 1) {
        transformedString.replace(pos, 2, replaceWith);
    }

    return transformedString;
}

std::string treatString(const std::string& input) {
    std::string treatedString = input;
    treatedString = replaceSeq(treatedString, "\\n", "\n");
    treatedString = replaceSeq(treatedString, "\\b", "\b");
    treatedString = replaceSeq(treatedString, "\\t", "\t");
    return treatedString;
}

void Eval::evalVarDecl() {
    if (this->node.left.value == "str") {
        this->strings[this->node.mid.value] = treatString(this->node.right.value);
        this->varTypes[this->node.mid.value] = "str";
        return;
    }
    this->ints[this->node.mid.value] = std::stoi(this->node.right.value.c_str());
    this->varTypes[this->node.mid.value] = "int";
}

Token Eval::getArg(int pos) {
    return this->node.innerNodes[pos].left;
}

void Eval::evalFunCall() {
    if (this->node.left.value == "print") {
        switch (this->getArg(0).type) {
            case TokType::str:
                printf("%s", treatString(this->getArg(0).value).c_str());
                break;
            case TokType::name:
                if (this->varTypes[this->getArg(0).value] == "str") {
                    printf("%s", this->strings[this->getArg(0).value].c_str());
                } else {
                    printf("%d", this->ints[this->getArg(0).value]);
                }
                break;
            case TokType::num:
                printf("%s", this->getArg(0).value.c_str());
                break;
        }
    }
}

void Eval::eval(std::vector<Node> ast) {
    this->ast = ast;
    
    for (Node node : ast) {
        this->node = node;
        switch (node.type) {
            case NodeType::varDecl:
                this->evalVarDecl();
                break;
            case NodeType::funCall:
                this->evalFunCall();
                break;
        }
    }
}