// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Node {
    public:
        string word;
        int count;
};

class Dict {
private:
    // You can add attributes/helper functions here
    int size;
    vector<vector<Node>>storage2d;
    int n[10] = {1, 41, 1681, 68921, 2825761, 5856201, 104241, 4273881, 5229121, 4393961};
    char sep[15] = {' ', '.', ',', '-', ':', '!', '"', '\'', '(', ')', '?', '[', ']', ';', '@'};

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
    int getSize(){
        return size;
    }
    
    bool bsep(char x){
        for (int i = 0; i<15;i++){
            if (sep[i]==x){
                return true;
            }
        }
        return false;
    }

    int hash(string id){
        int l = 0;
        for (int i = 0;i<id.size();i++){
            l+=(id[i]%10)*n[i%10];
        }
        l = l%10000000;
        return l;
    }

    void createWord(std::string word) {
        int h = hash(word);
        Node a;
        a.count = 1;
        a.word = word;
        storage2d[h].push_back(a);
        size+=1;
    }

    bool doesExist(string word) {
        int h = hash(word);
        for(int i = 0;i<storage2d[h].size();i++){
            if (storage2d[h][i].word == word){
                return true;
            }
        }
        return false;
    }

    void addCount(std::string word) {
        int h = hash(word);
        for(int i = 0;i<storage2d[h].size();i++){
            if (storage2d[h][i].word == word){
                storage2d[h][i].count+=1;
                break;
            }
        }
    }

    int getCount(std::string word) {
        int h = hash(word);
        for(auto x:storage2d[h]){
            if (x.word == word){
                return x.count;
            }
        }
        return -1; // Placeholder return value
    }
};