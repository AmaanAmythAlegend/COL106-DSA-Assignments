/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

SymbolTable::SymbolTable(){
    size = 0;
    root = nullptr;
}

SymEntry* ins(string k, UnlimitedRational* v, SymEntry* root){
    if (root==nullptr){
        root = new SymEntry(k, v);
        return root;
    }
    if(root->left==nullptr and k<root->key){
        root->left = new SymEntry(k, v);
        return root;
    }
    else if(root->right==nullptr and k>root->key){
        root->right = new SymEntry(k, v);
        return root;
    }
    else{
        if (k>root->key){
            root->right = ins(k, v, root->right);
            return root;
        }
        else{
            root->left = ins(k, v, root->left);
            return root;
        }
    }
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    root = ins(k, v, root);
    size+=1;
}

SymEntry* successor(SymEntry* root){
    SymEntry* temp = root->right;
    while (temp->left!=nullptr){
        temp = root->left;
    }
    return temp;
}

SymEntry* rem(string k, SymEntry* root){
    SymEntry* temp = root;
    if (temp->key>k){
        temp->left = rem(k, temp->left);
        return temp;
    }
    else if (temp->key<k){
        temp->right = rem(k, temp->right);
        return temp;
    }
    else{
        if (temp->right==nullptr and temp->left==nullptr){
            delete temp;
            return nullptr;
        }
        else if (temp->right==nullptr and temp->left!=nullptr){
            SymEntry* temp1 = temp->left;
            delete temp;
            return temp1;
        }
        else if (temp->right!=nullptr and temp->left==nullptr){
            SymEntry* temp1 = temp->right;
            delete temp;
            return temp1;
        }
        else{
            SymEntry* temp1 = successor(temp);
            temp->key = temp1->key;
            temp->right = rem(temp1->key, temp->right);
            return temp1;
        }
    }
}

SymEntry* sea(string k, SymEntry* root){
    if (root->key == k){
        return root;
    }
    else{
        if (k>root->key){
            return sea(k, root->right);
        }
        else{
            return sea(k, root->left);
        }
    }
}

void SymbolTable::remove(string k){
    root = rem(k, root);
    size-=1;
}

UnlimitedRational* SymbolTable::search(string k){
    return sea(k,root)->val;
}

SymEntry* SymbolTable::get_root(){
    return root;
}

int SymbolTable::get_size(){
    return size;
}

SymbolTable::~SymbolTable(){
    delete root;
}