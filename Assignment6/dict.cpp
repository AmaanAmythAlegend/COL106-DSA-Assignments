// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
    std::vector<std::vector<Node>> s(10000000);
    storage2d=s;
    size = 0;
}

Dict::~Dict(){
    // Implement your function here    
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    string word;
    for(int i = 0; i<sentence.length();i++){
        if (bsep(sentence[i])==true){
            for (int j = 0; j<word.length();j++){
                word[j] = tolower(word[j]);
            }
            if (doesExist(word)==false and word!=""){
                createWord(word);
            }
            else if(doesExist(word)==true and word!=""){
                addCount(word);
            }
            word = "";
        }
        else{
            word = word + sentence[i];
        }
    }
    if (word!=""){
        for (int j = 0; j<word.length();j++){
            word[j] = tolower(word[j]);
        }
        if (doesExist(word)==false){
            createWord(word);
        }
        else{
            addCount(word);
        }
        word = "";
    }
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here
    if (doesExist(word)==false){
        return 0;
    }
    else{
        return getCount(word);
    }
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    ofstream file(filename);
    int i = 0;
    while(i<storage2d.size()){
        if (storage2d[i].empty()==false){
            for (int j = 0;j < storage2d[i].size(); j++){
                file<<storage2d[i][j].word<<", "<<storage2d[i][j].count<<"\n";
            }
        }
        i++;
    }
    file.close();
    return;
}

