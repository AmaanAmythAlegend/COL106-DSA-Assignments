#include "stack_c.h"
#include "list.h"
#include "node.h"
#include <iostream>
#include <stdexcept>

using namespace std;

Stack_C::Stack_C(){
try{
stk = new List();
}
catch(...){
throw runtime_error("Out of Memory");
}
}

Stack_C::~Stack_C(){
delete stk;
}

void Stack_C::push(int n){
try{stk->insert(n);}
catch(...){
throw runtime_error("Out of Memory");
}
}

int Stack_C::pop(){
if (stk->get_size() == 0){
throw runtime_error("Empty Stack");
}
else{
int r = stk->delete_tail();
return r;
}
}

int Stack_C ::get_element_from_top(int idx){
int s = stk->get_size();
if (s-idx<1){
throw runtime_error("Index out of range");
}
Node* n = stk->get_head()->prev;
for (int i = 0;i<idx+1;i++){
    n = n->prev;
}
return n->get_value();
}

int Stack_C ::get_element_from_bottom(int idx){
int s = (*stk).get_size();
if (s-idx<1){
throw runtime_error("Index out of range");
}
Node* n = (*stk).get_head();
for(int i = 0;i<idx+1;i++){
n = n->next;
}
return n->get_value();
}

void Stack_C ::print_stack(bool top){
int s = (*stk).get_size();
if (s==0){
return;
}
Node* n = (*stk).get_head();
if (top==1){
n = n->prev;
for (int i = 0;i<s;i++){
n = n->prev;
cout<<n->get_value()<<endl;
}
}
else{
for(int i = 0; i<s;i++){
n = n->next;
cout<<n->get_value()<<endl;
}
}
}

int Stack_C ::add(){
int s = (*stk).get_size();
if (s<2){
throw runtime_error("Not Enough Arguements");
}
int a = stk->delete_tail();
int b = stk->delete_tail();
stk->insert(a+b);
return a+b;
}

int Stack_C ::subtract(){
int s = (*stk).get_size();
if (s<2){
throw runtime_error("Not Enough Arguements");
}
int a = stk->delete_tail();
int b = stk->delete_tail();
stk->insert(-a+b);
return -a+b;
}

int Stack_C ::multiply(){
int s = (*stk).get_size();
if (s<2){
throw runtime_error("Not Enough Arguements");
}
int a = stk->delete_tail();
int b = stk->delete_tail();
stk->insert(a*b);
return a*b;
}

int Stack_C ::divide(){
int s = (*stk).get_size();
if (s<2){
throw runtime_error("Not Enough Arguements");
}
int a = stk->delete_tail();
int b = stk->delete_tail();
if (a==0){
throw runtime_error("Divide by Zero Error");
}
int c = b/a;
if(c<=0){
c-=1;
}
stk->insert(c);
return c;
}

List* Stack_C ::get_stack(){
return stk;
}

int Stack_C ::get_size(){
return stk->get_size();
}

