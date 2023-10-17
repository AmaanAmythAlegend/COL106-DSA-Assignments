/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    size = 0;
    root = NULL;
}

int height(SymNode* node){
    if (node==NULL){
        return 0;
    }
    else{
        return max(height(node->left), height(node->right))+1;
    }
}

SymNode* ins(string k, SymNode* root){
    if (root==NULL){
        root = new SymNode(k);
    }
    else if (k>root->key){
        root->right = ins(k, root->right);
    }
    else if (k<root->key){
        root->left = ins(k, root->left);
    }
    
    int x = height(root->left);
    int y = height(root->right);
    root->height = 1 + max(x,y);

    int bal = x-y;

    if (bal>1){
        if (k<root->left->key){
            return root->RightRightRotation();
        }
        else{
            root->left = root->left->LeftLeftRotation();
            return root->RightRightRotation();
        }
    }
    else if (bal<-1){
        if (k<root->right->key){
            root->right = root->right->RightRightRotation();
            return root->LeftLeftRotation();
        }
        else{
            return root->LeftLeftRotation();
        }
    }
    else{
        return root;
    }
}


void SymbolTable::insert(string k){
    root = ins(k, root);
    size+=1;
}

SymNode* successor(SymNode* root){
    SymNode* temp = root->right;
    while (temp->left!=NULL){
        temp = temp->left;
    }
    return temp;
}

SymNode* rem(string k, SymNode* root){
    SymNode* temp = root;
    if (temp==NULL){
        return temp;
    }
    if (temp->key!=k){
        if (temp->key>k){
            temp->left = rem(k, temp->left);
        }
        else{
            temp->right = rem(k, temp->right);
        }
        int x = height(temp->left);
        int y = height(temp->right);
        temp->height = 1 + max(x,y);

        int bal = x-y;

        if (bal>1){
            if (k>temp->left->key){
                return temp->RightRightRotation();
            }
            else{
                return temp->LeftRightRotation();
            }
        }
        else if (bal<-1){
            if (k>temp->right->key){
                return temp->RightLeftRotation();
            }
            else{
                return temp->LeftLeftRotation();
            }
        }
        else{
            return temp;
        }
    }
    else{
        if (temp->right==NULL and temp->left==NULL){
            delete temp;
            return NULL;
        }
        SymNode* temp1;
        if (temp->right==NULL and temp->left!=NULL){
            temp1 = temp->left;
            delete temp;
        }
        else if (temp->right!=NULL and temp->left==NULL){
            temp1 = temp->right;
            delete temp;
        }
        else{
            temp1 = successor(temp);
            temp->key = temp1->key;
            temp->right = rem(temp1->key, temp->right);
        }
        int x = height(temp1->left);
        int y = height(temp1->right);
        temp1->height = 1 + max(x,y);

        int bal = x-y;

        if (bal>1){
            if (k>temp1->left->key){
                return temp1->RightRightRotation();
            }
            else{
                return temp1->LeftRightRotation();
            }
        }
        else if (bal<-1){
            if (k>temp1->right->key){
                return temp1->RightLeftRotation();
            }
            else{
                return temp1->LeftLeftRotation();
            }
        }
        else{
            return temp1;
        }
    }
}

void SymbolTable::remove(string k){
    root = rem(k, root);
    size-=1;
}


SymNode* sea(string k, SymNode* root){
    if (root==NULL){
        return NULL;
    }
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

int SymbolTable::search(string k){
    if (sea(k, root)==NULL){
        return -2;
    }
    else{
        return sea(k,root)->address;
    }
}

void SymbolTable::assign_address(string k,int idx){
    sea(k, root)->address = idx;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}