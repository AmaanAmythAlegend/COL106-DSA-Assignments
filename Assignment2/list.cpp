#include "list.h"
#include "node.h"
using namespace std;

List::List(){
size = 0;
sentinel_head = new Node(true);
sentinel_tail = new Node(true);
(*sentinel_head).next = sentinel_tail;
(*sentinel_tail).prev = sentinel_head;
(*sentinel_head).prev = sentinel_tail;
(*sentinel_tail).next = sentinel_head;
}

List::~List(){
delete sentinel_head;
delete sentinel_tail;
}

void List:: insert(int v){
if (size==0){
Node *n = new Node(v, sentinel_tail, sentinel_head);
sentinel_head->next = n;
sentinel_tail->prev = n;
size+=1;
}
else{
Node *n = new Node(v, sentinel_tail, (*sentinel_tail).prev);
(*(*sentinel_tail).prev).next = n;
(*sentinel_tail).prev = n;
size+=1;
}
}

int List:: delete_tail(){
Node* tempN = (*sentinel_tail).prev;
int r = (*tempN).get_value();
(*tempN).next = sentinel_tail;
(*sentinel_tail).prev = (*tempN).prev;
delete tempN;
size-=1;
return r;
}

int List:: get_size(){
return size;
}

Node* List:: get_head(){
return sentinel_head;
}