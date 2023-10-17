#include "evaluator.h"

    Evaluator::Evaluator()
    {

    }
    Evaluator::~Evaluator()
    {
        delete symtable;
    }
    UnlimitedRational* helper(ExprTreeNode* root,SymbolTable* symi)
    {
        UnlimitedRational* hero=new UnlimitedRational;
        if(root->type=="ADD")
        {
            root->evaluated_value=hero->add(helper(root->left,symi),helper(root->right,symi));
            return root->evaluated_value;
        }
        else if(root->type=="SUB")
        {
            root->evaluated_value=hero->sub(helper(root->left,symi),helper(root->right,symi));
            return root->evaluated_value;
        }
        else if(root->type=="MUL")
        {
            root->evaluated_value=hero->mul(helper(root->left,symi),helper(root->right,symi));
            return root->evaluated_value;
        }
        else if(root->type=="DIV")
        {
            root->evaluated_value=hero->sub(helper(root->left,symi),helper(root->right,symi));
            return root->evaluated_value;
        }
        else if(root->type=="VAL")
        {
            root->evaluated_value=root->val;
            return root->evaluated_value;
        }
        else
        {
             root->evaluated_value=symi->search(root->id);
            return root->evaluated_value;
        }

    }
    void Evaluator::parse(vector<string> code)
    {   
        
        int i=0;
        ExprTreeNode* baap=new ExprTreeNode();
        baap->type="EQUALS";
        baap->id="assign";
        ExprTreeNode* variable=new ExprTreeNode();
        variable->type="VAR";
        variable->id=code[0];
        baap->left=variable;
        i=2;
        ExprTreeNode* root=new ExprTreeNode;
        vector<ExprTreeNode*> pusher;
        pusher.push_back(root);
        while(i<code.size())
        {   
            if(code[i]=="(")
            {
                ExprTreeNode* dumm_node=new ExprTreeNode();
                root->left=dumm_node;
                pusher.push_back(root);
                root=dumm_node;
            }
            else if(code[i]=="+" || code[i]=="-" || code[i]=="*" || code[i]=="/" || code[i] =="%")
            {   if(code[i]=="+")
                root->type="ADD";
                if(code[i]=="%")
                root->type="MOD";
                if(code[i]=="/")
                root->type="DIV";
                if(code[i]=="*")
                root->type="MUL";
                if(code[i]=="-")
                root->type="SUB";
                ExprTreeNode* dumm_node=new ExprTreeNode();
                root->right=dumm_node;
                pusher.push_back(root);
                root=dumm_node;
            }
            else if(code[i]==")")
            {
                root=pusher.back();
                pusher.pop_back();
            }
            else
            {   string t=code[i];
                int danda;
                danda=1;
                int i=0;
                if(t[0]=='-' || isdigit(t[0]))
                {
                    i++;
                }
                else
                {
                    danda=0;
                }
                while(danda==1 && i<t.length())
                {
                    if(isdigit(t[i]))
                    i++;
                    else
                    danda=0;
                }
                if(danda==1)
                {
                    root->type="VAL";
                    root->val=new UnlimitedRational(new UnlimitedInt(code[i]),new UnlimitedInt(1));
                    
                }
                else
                {
                    root->type="VAR";
                    root->id=code[i];

                }
                    root=pusher.back();
                    pusher.pop_back();
            }
                i++;
        }
        baap->right=root;
        expr_trees.push_back(baap);
    }
    void Evaluator::eval()
    {
        ExprTreeNode* root=expr_trees.back();
        ExprTreeNode* ans=root->right;
        UnlimitedRational* vally=helper(ans,symtable);
        ans->evaluated_value=vally;
        root->left->evaluated_value=vally;
        symtable->insert(root->left->id,vally);
    }