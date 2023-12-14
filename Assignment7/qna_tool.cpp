#include <assert.h>
#include <sstream>
#include "qna_tool.h"
#include "Node.h"

using namespace std;

QNA_tool::QNA_tool(){
 corpus=new Dict();
     //vector<dictpairs*> astha;
    // Dict* corpus;x
    // Implement your function here  
}

QNA_tool::~QNA_tool(){
    // Implement your function here  
}
Node* strintonode(string s){
    Node* current=new Node();
    vector<string> v;
    string ans="";
    for(int i=0;i<s.size();i++){
        if(s[i]==','){
            v.push_back(ans);
            ans="";
        }
        else{
            ans+=s[i];
        }
    }
    if(ans!=""){
        v.push_back(ans);
    }
 
    current->book_code=stoi(v[0]);
    current->page=stoi(v[1]);
    current->paragraph=stoi(v[2]);
    return current;
}
long long givecount(string word){
    std::ifstream file("unigram_freq.csv");  // Change this to the word you want to find
    std::string line, words, count_str;

    while (getline(file, line)) {
        std::istringstream iss(line);
        getline(iss, words, ',');
        getline(iss, count_str, '\n');

        if (words == word) {
            return stoll(count_str); // Assuming you only want to find the count once
        }
    }
    file.close();

    return 1;
  
}
int giveindex(vector<tpairs*> v,string s){
    int cnt=0;
    for(auto x:v){
        if(x->val==s){
            return cnt;
        }
        cnt++;
    }
    return -1;
}
void QNA_tool::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    // cout<<1<<endl;
    string s=to_string(book_code)+","+to_string(page)+","+to_string(paragraph);
    if(astha.empty() or astha.back()->val!=s){
        Dict* d=new Dict();
        d->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
        astha.push_back(new dictpairs(s,d));
    }
    else{
    if(astha.back()->val==s){
        astha.back()->count->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    }
    }
    //out<<"inserted"<<endl;
    corpus->insert_sentence(book_code,page,paragraph,sentence_no,sentence);
    //cout<<"not"<<endl;

    return;
}
Node* recursiveReverse(Node* head) {
	Node* first;
	if (head==nullptr || head->right == nullptr)
		return head;

	first = recursiveReverse(head->right);
	head->right->right = head;
	head->right = nullptr;

	return first;
}

long double bm25(int no_of_para,int no_of_paras,int total_words,long double freq){
    long double log_term=log(no_of_para/(1+no_of_paras));
    long double num=2.5*freq;
    long double denom=freq+1.5*(0.25+0.75*(total_words));
    return (log_term*num)/denom;
}

Node* QNA_tool::get_top_k_para(string question, int k) {
    // Implement your function here
    vector<string> word;
    string separators=".,-:!\"'()?—[]˙;@ ";
    string ans;
    int no_of_para=astha.size();
    for(int i=0;i<question.size();i++){
        if(separators.find(question[i]) == std::string::npos){
            if(isupper(question[i])){
                ans+=tolower(question[i]);
            }
            else{
                ans+=question[i];
            }
        }
        else{
            if(ans!=""){
            word.push_back(stemmer.stemmed_word(ans));
            ans="";
            }
        }
    }
    if(ans!=""){
       word.push_back(stemmer.stemmed_word(ans));
    }

    Trie* scorekeeper = new Trie(); 
    int total_words=0;
    for(int i=0;i<astha.size();i++){
        total_words+=astha[i]->count->get_tree()->size;
    }
    total_words=total_words/no_of_para;
    for(int i=0;i<word.size();i++){
        int no_of_paras=0;
        for(int k=0;k<astha.size();k++){
            long double off=astha[k]->count->get_word_count(word[i]);
            if(off!=0){
                no_of_paras++;
            }
        }
        // long long wordcount=corpus->get_word_count(word[i]);
        // long long givecsv=givecount(word[i]);
        
        for(int j=0;j<astha.size();j++){
            long double off=astha[j]->count->get_word_count(word[i]);
            int no_of_words=astha[j]->count->get_tree()->size;
            NodeTrie* maki=scorekeeper->search(astha[j]->val);
            //cout<<"maki"<<endl;
            if(maki!=nullptr){
                maki->count+=bm25(no_of_para,no_of_paras,total_words,off);
                cout<<maki->count<<endl;
        }
        else{
            
            scorekeeper->insert(astha[j]->val);
            NodeTrie* mako=scorekeeper->search(astha[j]->val);
            mako->count+=bm25(no_of_para,no_of_paras,total_words,off);
             //cout<<"as"<<endl;
        }
        }
    }
    vector<NodeTrie*> result;
scorekeeper->getAllNodes(scorekeeper->root, "", result);
BinaryHeap* bp = new BinaryHeap();
Node* head1 = new Node();

for (int i = 0; i < result.size(); i++) {
    // cout<<result[i]->whatisword<<endl;
    bp->insert(result[i]->count,result[i]->whatisword);  // Assuming you want to use an empty string as a placeholder, replace it accordingly
    if (bp->heap.size() > k) {
        bp->deleteMin();
    }
}

head1 = strintonode(bp->minElem()->val);
bp->deleteMin();
Node* current1 = head1;

while (bp->heap.size() != 0) {
    current1->right = strintonode(bp->minElem()->val);
    bp->deleteMin();
    current1 = current1->right;
}
current1->right = nullptr;

return recursiveReverse(head1);

}



void QNA_tool::query(string question, string filename){
    // Implement your function here  
    Node* head = get_top_k_para(question, 3);
    query_llm(filename, head, 3, "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","What were the views of Mahatma on partition?");
    return;
}

std::string QNA_tool::get_paragraph(int book_code, int page, int paragraph){

    cout << "Book_code: " << book_code << " Page: " << page << " Paragraph: " << paragraph << endl;
    
    std::string filename = "mahatma-gandhi-collected-works-volume-";
    filename += to_string(book_code);
    filename += ".txt";

    std::ifstream inputFile(filename);

    std::string tuple;
    std::string sentence;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file " << filename << "." << std::endl;
        exit(1);
    }

    std::string res = "";

    while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
        // Get a line in the sentence
        tuple += ')';

        int metadata[5];
        std::istringstream iss(tuple);

        // Temporary variables for parsing
        std::string token;

        // Ignore the first character (the opening parenthesis)
        iss.ignore(1);

        // Parse and convert the elements to integers
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            // Trim leading and trailing white spaces
            size_t start = token.find_first_not_of(" ");
            size_t end = token.find_last_not_of(" ");
            if (start != std::string::npos && end != std::string::npos) {
                token = token.substr(start, end - start + 1);
            }
            
            // Check if the element is a number or a string
            if (token[0] == '\'') {
                // Remove the single quotes and convert to integer
                int num = std::stoi(token.substr(1, token.length() - 2));
                metadata[idx] = num;
            } else {
                // Convert the element to integer
                int num = std::stoi(token);
                metadata[idx] = num;
            }
            idx++;
        }

        if(
            (metadata[0] == book_code) &&
            (metadata[1] == page) &&
            (metadata[2] == paragraph)
        ){
            res += sentence;
        }
    }

    inputFile.close();
    return res;
}

void QNA_tool::query_llm(string filename, Node* root, int k, string API_KEY, string question){

    // first write the k paragraphs into different files

    Node* traverse = root;
    int num_paragraph = 0;

    while(num_paragraph < k){
        assert(traverse != nullptr);
        string p_file = "paragraph_";
        p_file += to_string(num_paragraph);
        p_file += ".txt";
        // delete the file if it exists
        remove(p_file.c_str());
        ofstream outfile(p_file);
        string paragraph;
        get_paragraph(traverse->book_code, traverse->page, traverse->paragraph);
        assert(paragraph != "$I$N$V$A$L$I$D$");
        outfile << paragraph;
        outfile.close();
        traverse = traverse->right;
        num_paragraph++;
    }

    // write the query to query.txt
    ofstream outfile("query.txt");
    outfile << "These are the excerpts from Mahatma Gandhi's books.\nOn the basis of this, ";
    outfile << question;
    // You can add anything here - show all your creativity and skills of using ChatGPT
    outfile.close();
 
    // you do not need to necessarily provide k paragraphs - can configure yourself

    // python3 <filename> API_KEY num_paragraphs query.txt
    string command = "python3 ";
    command += filename;
    command += " ";
    command += API_KEY;
    command += " ";
    command += to_string(k);
    command += " ";
    command += "query.txt";

    system(command.c_str());
    return;
}