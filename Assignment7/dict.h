// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
#include "stemmer.cpp"
#pragma once
using namespace std;
class pairs{
    public:
        long double count;
        string val;
        pairs(){
            count=0;
        }
        pairs(string k){
            count=0;
            val=k;
        }

};
class node{
    public:
        int key;
        int height;
        vector<pairs*> list;
        //red 1 black 0
        node* parent;
        node* left;
        node* right;

        node(){

            height=0;
            parent=nullptr;
            left=nullptr;
            right=nullptr;
        }
        node(int k){
            
            height=0;
            parent=nullptr;
            left=nullptr;
            right=nullptr;
            key=k;

        }

int heightnew(node* root){
    if(root==NULL){
        return 0;
    }
    int lefth=heightnew(root->left);
    int righth=heightnew(root->right);
    return 1+max(righth,lefth);
    
}
node* LeftLeftRotation(){
    node* newroot=this->right;
    this->right=newroot->left;
    newroot->left=this;
    this->height=heightnew(this);
    newroot->height=heightnew(newroot);
    return newroot;
}

node* RightRightRotation(){
    node* newroot=this->left;
    this->left=newroot->right;
    newroot->right=this;
    this->height=heightnew(this);
    newroot->height=heightnew(newroot);
    return newroot;

}

node* LeftRightRotation(){
    this->right=this->right->RightRightRotation();
    return this->LeftLeftRotation();

}

node* RightLeftRotation(){
    this->left=this->left->LeftLeftRotation();
    return this->RightRightRotation();
}

};
class avltree{
    node* root;
   
    public:
     int size;
        avltree(){
            root=nullptr;
            size=0;
        }
        int heightnews(node* root){
    if(root==NULL){
        return 0;
    }
    int lefth=heightnews(root->left);
    int righth=heightnews(root->right);
    return 1+max(righth,lefth);
    
}
int balancefactor(node* root){
    if(!root){
        return 0;
    }
    int lefth=heightnews(root->left);
    int righth=heightnews(root->right);

    return righth-lefth;
}
int hash(string k){
    int x=0;

    for(int i=0;i<k.length();i++){
        x=x+(int)k[i];
    }
    return x;
}
node* inserthelp(node* root,string k){
    int hashid=hash(k);
    if(root==NULL){
        node* current=new node(hashid);
        pairs* p=new pairs(k);
        p->count++;
        current->list.push_back(p);
        return current;
    }
    if(hashid<root->key){
        root->left=inserthelp(root->left,k);
    }
    else if(hashid>root->key){
        root->right=inserthelp(root->right,k);
    }
    else{
        pairs* p=new pairs(k);
        p->count++;
        root->list.push_back(p);
        return root;
    }
    root->height=max(heightnews(root->left), heightnews(root->right))+1;
    int balance=balancefactor(root);
    if(balance>1){
        if(balancefactor(root->right)<0){
            root=root->LeftRightRotation();
        }
        else{
            root=root->LeftLeftRotation();
        }
    }
    else if(balance<-1){
        if(balancefactor(root->left)>0){
            root=root->RightLeftRotation();

        }
        else{
            root=root->RightRightRotation();
        }
    }
    return root;
}

void insert(string k){
    if(search(k)==0){
        root=inserthelp(root,k);
        size++;
    }
    else{
        pairs* current=searched(k);
        current->count++;

    }
    

}




int search(string k){
    int hashid=hash(k);
    node* current=root;
    while(current!=NULL){
        if(current->key>hashid){
            current=current->left;
        }
        else if(current->key<hashid){
            current=current->right;
        }
        else{
            vector<pairs*> v=current->list;
            // cout<<v.size()<<endl;
            for(int i=0;i<v.size();i++){
                if(v[i]->val==k){
                    return 1;
                }
            }

            return 0;
        }
    }
    return 0;

}
pairs* searched(string k){
    int hashid=hash(k);
    node* current=root;
    while(current->key!=hashid){
        if(current->key>hashid){
            current=current->left;
        }
        else{
            current=current->right;
        }
    }
    vector<pairs*> v=current->list;
    for(int i=0;i<v.size();i++){
        if(v[i]->val==k){
            return v[i];
        }
    }

}



int get_size(){
    return size;

}

node* get_root(){
    return root;

}


};
class Dict {
private:

    avltree* tree;
    Porter_Stemmer stemmer;
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    long long get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
    avltree* get_tree();
};