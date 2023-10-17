/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){

}

int num_nodes(HeapNode* node){
    if (node==NULL){
        return 0;
    }
    else{
        return 1+num_nodes(node->left)+num_nodes(node->right);
    }
}

void MinHeap::push_heap(int num){
    if 
}

int MinHeap::get_min(){

}

void MinHeap::pop(){

}

MinHeap::~MinHeap(){

}