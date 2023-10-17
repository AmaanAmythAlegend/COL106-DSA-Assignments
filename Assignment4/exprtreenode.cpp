/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

using namespace std;

ExprTreeNode::ExprTreeNode(){
    type = "";
    val = NULL;
    left = nullptr;
    right = nullptr;
    evaluated_value = nullptr;
    id = "";    
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    left = nullptr;
    right = nullptr;
    if (t == "+"){
        type = "ADD";
    }
    else if (t == "-"){
        type = "SUB";
    }
    else if (t == "*"){
        type = "MUL";
    }
    else if (t == "/"){
        type = "DIV";
    }
    else{
        bool c = 1;
        for(int i = 0; i<t.length(); i++){
            if (t[i]-'0'>9 or t[i]-'0'<0){
                c = 0;
                if (!(i==0 and t[i]=='-')){
                    c = 0;
                }
                else{
                    c = 1;
                }
            }
        }
        if (c){
            type = "VAL";
            val = new UnlimitedRational(v, new UnlimitedInt("1"));
        }
        else if (t==":="){
            type = "ASS";
            id = t;
        }
        else{
            type = "VAR";
            id = t;
        }
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    left = nullptr;
    right = nullptr;
    if (t == "+"){
        type = "ADD";
    }
    else if (t == "-"){
        type = "SUB";
    }
    else if (t == "*"){
        type = "MUL";
    }
    else if (t == "/"){
        type = "DIV";
    }
    else{
        bool c = 1;
        for(int i = 0; i<t.length(); i++){
            if (t[i]-'0'>9 or t[i]-'0'<0){
                c = 0;
                if (v->get_frac_str()!=t){
                    c = 0;
                }
                else{
                    c = 1;
                }
            }
        }
        if (c){
            type = "VAL";
            val = v;
        }
        else if (t==":="){
            type = "ASS";
            id = t;
        }
        else{
            type = "VAR";
            id = t;
        }
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}
