/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = 0;i < mem_limit;i++){
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    for (int i = 0; i < code.size(); i++){
        targ.parse(code[i]);
        vector<string> com;
        if (code[i][0]=="del"){
            mem_loc.push_back(targ.symtable->search(code[i][2]));
            com = generate_targ_commands();
            targ.symtable->remove(code[i][2]);
        }
        else if (code[i][0]!="ret"){
            if (targ.symtable->search(code[i][0])==-2){
                targ.symtable->insert(code[i][0]);
                int x = mem_loc.back();
                mem_loc.pop_back();
                targ.symtable->assign_address(code[i][0], x);
            }
            com = generate_targ_commands();
        }
        else{

            com = generate_targ_commands();
        }
        
        write_to_file(com);
    }
}

void postorder(vector<string> &t, ExprTreeNode* root, Parser &targ){
    if (root==NULL){
        return;
    }
    if (root->type=="VAL"){
        string val = to_string(root->num);
        t.push_back("PUSH " + val);
    }
    else if (root->type=="VAR"){
        t.push_back("PUSH mem["+to_string(targ.symtable->search(root->id))+"]");
    }
    else if (root->type!="DEL" and root->type!="RET"){
        postorder(t, root->right, targ);
        postorder(t, root->left, targ);
        t.push_back(root->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> t;
    ExprTreeNode* temp = targ.expr_trees.back();
    if (temp->left->type == "VAR"){
        postorder(t, temp->right, targ);
        t.push_back("mem["+to_string(targ.symtable->search(temp->left->id))+"] = POP");
    }
    else if (temp->left->type == "DEL"){
        t.push_back("DEL = mem["+to_string(targ.symtable->search(temp->right->id))+"]");
    }
    else{
        postorder(t, temp->right, targ);
        t.push_back("RET = POP");
    }
    return t;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream to_file;
    to_file.open(output_file, ios::app);
    for (int i = 0; i < commands.size(); i++){
        to_file<<commands[i]<<endl;
    }
    to_file.close();
}

EPPCompiler::~EPPCompiler(){

}