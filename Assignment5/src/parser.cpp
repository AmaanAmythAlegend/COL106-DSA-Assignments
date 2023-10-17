/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable = new SymbolTable();
}

ExprTreeNode* help(vector<string> code, int i, int j){
    i+=1;
    j-=1;
    if (i>j){
        bool c = 1;
        for(int k = 0; k<code[i-1].length(); k++){
            if (code[i-1][k]-'0'>9 or code[i-1][k]-'0'<0){
                c = 0;
                if (k==0 and code[i-1][k]=='-'){
                    c = 1;
                }
            }
        }
        if (c){
            return new ExprTreeNode(code[i-1], stoi(code[i-1]));
        }
        else{
            return new ExprTreeNode(code[i-1], 0);
        }
    }
    int k;
    ExprTreeNode* left_node;
    if (code[i]=="("){
        k = i;
        int c = 0;
        while(code[k]!=")" or c!=1){
            if (code[k]=="("){
                c+=1;
            }
            else if (code[k]==")"){
                c-=1;
            }
            k+=1;
        }
        k+=1;
        left_node = help(code, i, k);
    }
    else{
        k = i;
        k+=1;
        left_node = help(code, i, k);
    }

    ExprTreeNode* node = new ExprTreeNode(code[k], 0);

    k = k+1;
    ExprTreeNode* right_node = help(code, k, j);

    node->left = left_node;
    node->right = right_node;
    return node;
}

void Parser::parse(vector<string> expression){
    if (expression[0]=="del"){
        ExprTreeNode* root = new ExprTreeNode(":=", 0);
        root->left = new ExprTreeNode();
        root->left->type = "DEL";
        root->left->id = "DEL";
        root->right = help(expression, 2, expression.size());
        expr_trees.push_back(root);
    }
    else if (expression[0]=="ret"){
        ExprTreeNode* root = new ExprTreeNode(":=", 0);
        root->left = new ExprTreeNode();
        root->left->type = "RET";
        root->left->id = "RET";
        root->right = help(expression, 2, expression.size());
        expr_trees.push_back(root);
    }
    else{
        ExprTreeNode* root = new ExprTreeNode(":=", 0);
        root->left = new ExprTreeNode();
        root->left->type = "VAR";
        root->left->id = expression[0];
        root->right = help(expression, 2, expression.size());
        expr_trees.push_back(root);
    }
}

Parser::~Parser(){
    delete symtable;
    expr_trees.clear();
}