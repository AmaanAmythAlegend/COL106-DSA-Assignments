
#include <iostream>
#include <fstream>
#include "Node.h"

#include<cmath>
#include "dict.h"


using namespace std;

class NodeTrie{
    public:
    NodeTrie* children[58];
    long double count;
    bool isendofword;
    string whatisword;
    NodeTrie(){
        for(int i=0;i<58;i++){
            children[i]=nullptr;
        }
        isendofword=false;
        count=0;

    }
};

class Trie {
   

public:
    NodeTrie* root;
    Trie() {
        root = new NodeTrie();
    }
    
    void insert(string word) {
        NodeTrie* current = root;
        for (int i = 0; i < word.size(); i++) {
            if (current->children[word[i] - ','] == nullptr) {
                current->children[word[i] - ','] = new NodeTrie();
            }
            current = current->children[word[i] - ','];
        }
        current->isendofword = true;
        current->whatisword=word;
    }

    NodeTrie* search(string word) {
        NodeTrie* current = root;
        for (int i = 0; i < word.size(); i++) {
            if (current->children[word[i] - ','] == nullptr) {
                //cout<<"astha"<<endl;
                return nullptr;
            }
            current = current->children[word[i] - ','];
        }
        if (current->isendofword) {
            return current;
        } else {
            return nullptr;
        }
    }

    void getAllNodes(NodeTrie* current, std::string currentWord, std::vector<NodeTrie*>& result) {
    if (current == nullptr) {
        return;
    }

    if (current->isendofword) {
        result.push_back(current);
        // Print or use 'currentWord' as needed
        //std::cout << currentWord << std::endl;
    }

    for (int i = 0; i < 58; ++i) {
        if (current->children[i] != nullptr) {
            char ch = 'a' + i;
            getAllNodes(current->children[i], currentWord + ch, result);
        }
    }

}
 
};




class dictpairs{
    public:
        Dict* count;
        string val;
        dictpairs(){
            count=new Dict();
            val="";
        }
        dictpairs(string k){
            count=new Dict();
            val=k;
        }
        dictpairs(string k,Dict* d){
            count=d;
            val=k;
        }

};
class tpairs{
    public:
        long double count;
        string val;
        tpairs(){
            count=0;
        }
        tpairs(string k){
            count=0;
            val=k;
        }
        tpairs(string k,long double d){
            val=k;
            count=d;
        }

};
class BinaryHeap {


public:
std::vector<tpairs*> heap;
  void swap(tpairs* &a, tpairs* &b) {
        tpairs* temp = a;
        a = b;
        b = temp;
    }

  int getParentIndex(int i) {
    return (i - 1) / 2;
  }
  
  int getLeftChildIndex(int i) {
    return 2 * i + 1;
  }
  
  int getRightChildIndex(int i) {
    return 2 * i + 2;
  }
  

  void insert(long double score,string para) {
    heap.push_back(new tpairs(para,score)); //satisfies the structural prop
    heapifyUp(heap.size() - 1);
  }

  void heapifyUp(int index) {
    if (index == 0) return; // base condition for termination of a recursive invocation of the fnc
    
    int parentIndex = getParentIndex(index);
    
    if (heap[parentIndex]->count > heap[index]->count) {
      swap(heap[parentIndex], heap[index]);
      heapifyUp(parentIndex);
    }
  }
  
  void heapifyDown(int index) {
    int leftChild = getLeftChildIndex(index);
    int rightChild = getRightChildIndex(index);
    
    if (leftChild >= heap.size()) return; // No children
    
    int minIndex = index;
    
    if (heap[minIndex]->count > heap[leftChild]->count) {
      minIndex = leftChild;
    }
    
    if (rightChild < heap.size() && heap[minIndex]->count > heap[rightChild]->count) {
      minIndex = rightChild;
    }
    
    if (minIndex != index) {
      swap(heap[minIndex], heap[index]);
      heapifyDown(minIndex);
    }
  }

  void heapifyDown(int n, int index) {
    int leftChild = getLeftChildIndex(index);
    int rightChild = getRightChildIndex(index);
    
    int minIndex = index;
    
    if (leftChild < n && heap[minIndex]->count > heap[leftChild]->count) {
      minIndex = leftChild;
    }
    
    if (rightChild < n && heap[minIndex]->count > heap[rightChild]->count) {
      minIndex = rightChild;
    }
    
    if (minIndex != index) {
      swap(heap[minIndex], heap[index]);
      heapifyDown(n, minIndex);
    }
  }

  tpairs* minElem(){
    return heap[0];
  }
  //replace root with last element of the heap
 void deleteMin() {
    
    heap[0] = heap.back();
    heap.pop_back();
    
    heapifyDown(0);
  }
  
  
  void buildHeap(const std::vector<tpairs*> &arr, int size) {

    for (int i = 0; i < size; i++)
      heap.push_back(arr[i]);
    
    int n = size;
    
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapifyDown(i);
    }
  }
};

class QNA_tool {

private:

    // You are free to change the implementation of this function
    void query_llm(string filename, Node* root, int k, string API_KEY, string question);
    // filename is the python file which will call ChatGPT API
    // root is the head of the linked list of paragraphs
    // k is the number of paragraphs (or the number of nodes in linked list)
    // API_KEY is the API key for ChatGPT
    // question is the question asked by the user

    // You can add attributes/helper functions here

public:
    vector<dictpairs*> astha;
    Dict* corpus;
    Porter_Stemmer stemmer;
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    
    QNA_tool(); // Constructor
    ~QNA_tool(); // Destructor

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);
    // This function is similar to the functions in dict and search 
    // The corpus will be provided to you via this function
    // It will be called for each sentence in the corpus

    Node* get_top_k_para(string question, int k);
    // This function takes in a question, preprocess it
    // And returns a list of paragraphs which contain the question
    // In each Node, you must set: book_code, page, paragraph (other parameters won't be checked)

    //std::string get_paragraph(int book_code, int page, int paragraph);//
    // Given the book_code, page number, and the paragraph number, returns the string paragraph.
    // Searches through the corpus.

    void query(string question, string filename);
    // This function takes in a question and a filename.
    // It should write the final answer to the specified filename.

    /* -----------------------------------------*/
    /* Please do not touch the code above this line */
    string get_paragraph(int book_code, int page, int paragraph);
    // You can add attributes/helper functions here
};