// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    // Implement your function here   
}

SearchEngine::~SearchEngine(){
    // Implement your function here
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    vector<string> v;
    v.push_back(to_string(book_code));
    v.push_back(to_string(page));
    v.push_back(to_string(paragraph));
    v.push_back(to_string(sentence_no));
    v.push_back(sentence);

    s.push_back(v);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here
    n_matches = 0;
    Node* head = new Node();
    int m = pattern.length();
    int mat = 0;
    for (int l = 0; l < m; l++){
        mat+=tolower(pattern[l]);
    }

    for (int i = 0; i<s.size();i++){
        int hash = 0;
        if (m<=s[i][4].length()){
            for (int j = 0; j<s[i][4].length()-m+1; j++){
                if (j==0){
                    for (int k = 0; k < m; k++){
                        hash+=tolower(s[i][4][k]);
                    }
                }
                else{
                    hash-=tolower(s[i][4][j-1]);
                    hash+=tolower(s[i][4][j+m-1]);
                }
                if (hash==mat){
                    string pa = "";
                    for (int o = 0; o < m; o++){
                        pa+=tolower(s[i][4][j+o]);
                    }
                    if (pa==pattern){
                        Node* n = new Node(stoi(s[i][0]), stoi(s[i][1]), stoi(s[i][2]), stoi(s[i][3]), j);
                        if (n_matches==0){
                            head = new Node(stoi(s[i][0]), stoi(s[i][1]), stoi(s[i][2]), stoi(s[i][3]), j);
                            n_matches++;
                        }
                        else{
                            Node* newnode = new Node(stoi(s[i][0]), stoi(s[i][1]), stoi(s[i][2]), stoi(s[i][3]), j);
                            newnode->left = nullptr;
                            newnode->right = head;
                            head->left = newnode;
                            head = newnode;
                            n_matches++;
                        }
                    }
                }
            }
        }
    }  
    return head;
}
