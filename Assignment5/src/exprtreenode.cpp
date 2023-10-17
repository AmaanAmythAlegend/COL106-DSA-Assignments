/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type = "";
    num = 0;
    left = NULL;
    right = NULL;
    id = ""; 
}

ExprTreeNode::ExprTreeNode(string t,int v){
    left = NULL;
    right = NULL;
    if (t == "+"){
        type = "ADD";
        id = "+";
    }
    else if (t == "-"){
        type = "SUB";
        id = "-";
    }
    else if (t == "*"){
        type = "MUL";
        id = "*";
    }
    else if (t == "/"){
        type = "DIV";
    }
    else{
        bool c = 1;
        for(int i = 0; i<t.length(); i++){
            if (t[i]-'0'>9 or t[i]-'0'<0){
                c = 0;
                if (i==0 and t[i]=='-'){
                    c = 1;
                }
                else{
                    break;
                }
            }
        }
        if (c){
            type = "VAL";
            num = v;
        }
        else if (t==":="){
            type = "ASS";
            id = t;
        }
        else if (t=="del"){
            type = "DEL";
            id = "DEL";
        }
        else if (t=="ret"){
            type = "RET";
            id = "RET";
        }
        else{
            type = "VAR";
            id = t;
        }
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right;
}

