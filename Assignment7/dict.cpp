// Do NOT add any other includes
#include "dict.h"


Dict::Dict(){
    tree = new avltree();
    // Implement your function here    
}
Dict::~Dict() { // Delete the entire AVL tree
    delete tree; // Delete the avltree object
}

string lowerconvert(string k){
    string ans;
    for(int i=0;i<k.size();i++){
        if(isupper(k[i])){
            ans+=tolower(k[i]);
        }
        else{
            ans+=k[i];
        }

    }
    return ans;
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string separators=".,-:!\"'()?—[]˙;@ ";
    string ans;
    for(int i=0;i<sentence.size();i++){
        if(separators.find(sentence[i]) == std::string::npos){
            if(isupper(sentence[i])){
                ans+=tolower(sentence[i]);
            }
            else{
                ans+=sentence[i];
            }
        }
        else{
            if(ans!=""){
            tree->insert(stemmer.stemmed_word(ans));
            ans="";
            }
        }
    }
    if(ans!=""){
        tree->insert(stemmer.stemmed_word(ans));
    }
    return;
}

long long Dict::get_word_count(string word){
    if(tree->search(stemmer.stemmed_word(word))==1){
    pairs* current=tree->searched(stemmer.stemmed_word(word));
    return current->count;
    }

else{
    return 0;
}
}
void inorder(node* root, std::ofstream& outFile) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left, outFile);
    for(int i=0;i<root->list.size();i++){
    outFile << root->list[i]->val << ", " << root->list[i]->count << "\n";
    }
    inorder(root->right, outFile);
}
void Dict::dump_dictionary(string filename) {
    std::ofstream outFile(filename);
    inorder(tree->get_root(), outFile);
    outFile.close();
}
avltree* Dict::get_tree(){
    return tree;
}

// int main(){
//     Dict* d=new Dict();
//     d->insert_sentence(1,1,2,1,"astha");
//     cout<<d->get_word_count("astha")<<endl;
//     return 0;
// }