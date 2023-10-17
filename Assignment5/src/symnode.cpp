/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key = "";
    height = -1;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* r = this->right;
    SymNode* l = r->left;

    r->left = this;
    this->right = l;

    return r;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* l = this->left;
    SymNode* r = l->right;

    l->right = this;
    this->left = r;

    return l;
}

SymNode* SymNode::LeftRightRotation(){
    this->left = this->left->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode* SymNode::RightLeftRotation(){
    this->right = this->right->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode::~SymNode(){
    key = "";
    delete left;
    delete right;
}