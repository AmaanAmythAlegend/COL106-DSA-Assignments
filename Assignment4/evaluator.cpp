/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

using namespace std;

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    while(!(expr_trees.empty())){
        ExprTreeNode* temp = expr_trees.back();
        expr_trees.pop_back();
        delete temp;
    }
    delete symtable;
}

ExprTreeNode* help(vector<string> code, int i, int j){
    i+=1;
    j-=1;
    if (i>j){
        bool c = 1;
        for(int k = 0; k<code[i-1].length(); k++){
            if (code[i-1][k]-'0'>9 or code[i-1][k]-'0'<0){
                c = 0;
                if (!(k==0 and code[i-1][k]=='-')){
                    c = 0;
                }
                else{
                    c = 1;
                }
            }
        }
        if (c){
            return new ExprTreeNode(code[i-1], new UnlimitedInt(code[i-1]));
        }
        else{
            return new ExprTreeNode(code[i-1], new UnlimitedInt());
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

    ExprTreeNode* node = new ExprTreeNode(code[k], new UnlimitedInt());

    k = k+1;
    ExprTreeNode* right_node = help(code, k, j);

    node->left = left_node;
    node->right = right_node;
    return node;
}

UnlimitedRational* evaluate(ExprTreeNode* root, SymbolTable* symtable){
    if (root->type=="ADD"){
        root->evaluated_value = UnlimitedRational::add(evaluate(root->left, symtable), evaluate(root->right, symtable));
        return root->evaluated_value;
    }
    else if (root->type=="SUB"){
        root->evaluated_value = UnlimitedRational::sub(evaluate(root->left, symtable), evaluate(root->right, symtable));
        return root->evaluated_value;
    }
    else if (root->type=="MUL"){
        root->evaluated_value = UnlimitedRational::mul(evaluate(root->left,symtable), evaluate(root->right,symtable));
        return root->evaluated_value;
    }
    else if (root->type=="DIV"){
        root->evaluated_value = UnlimitedRational::div(evaluate(root->left,symtable), evaluate(root->right, symtable));
        return root->evaluated_value;
    }
    else if (root->type=="VAL"){
        root->evaluated_value = root->val;
        return root->evaluated_value;
    }
    else if (root->type=="VAR"){
        root->evaluated_value = symtable->search(root->id);
        return root->evaluated_value;
    }
    else{
        return nullptr;
    }
}

void Evaluator::parse(vector<string> code){
    ExprTreeNode* root = new ExprTreeNode(":=", new UnlimitedInt());
    root->left = new ExprTreeNode();
    root->left->type = "VAR";
    root->left->id = code[0];
    root->right = help(code, 2, code.size());
    expr_trees.push_back(root);
}

void Evaluator::eval(){
    ExprTreeNode* root = expr_trees.back();
    root->evaluated_value = evaluate(root->right, symtable);
    symtable->insert(root->left->id, root->evaluated_value);
}
