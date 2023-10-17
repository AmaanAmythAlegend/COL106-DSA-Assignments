#include "stack_a.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Stack_A::Stack_A(){
size = 0;
}

void Stack_A:: push(int n){

if (size==1024){
throw runtime_error("Stack Full");
}

stk[size] = n;
size+=1;
}

int Stack_A:: pop(){
if (size==0){
throw runtime_error("Empty Stack");
}
size-=1;
return stk[size];
}

int Stack_A:: get_element_from_top(int idx){
if (size-idx<1){
throw runtime_error("Index out of range");
}
return stk[size-idx-1];
}

int Stack_A:: get_element_from_bottom(int idx){
if (size-idx<1){
throw runtime_error("Index out of range");
}
return stk[idx];
}

void Stack_A:: print_stack(bool top){
if (size==0){
return;
}
if (top==1){
for(int i=0;i<size;i++){
cout<<stk[size-i-1]<<"\n";
}
}
else{
for(int j=0;j<size;j++){
cout<<stk[j]<<"\n";
}
}
}

int Stack_A:: add(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
int a = this->pop();
int b = this->pop();
this->push(a+b);
return a+b;
}

int Stack_A:: subtract(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
int a = this->pop();
int b = this->pop();
this->push(-a+b);
return -a+b;
}

int Stack_A:: multiply(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
int a = this->pop();
int b = this->pop();
this->push(a*b);
return a*b;
}

int Stack_A:: divide(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
if (stk[size-1]==0){
throw runtime_error("Divide by Zero Error");
}
int a = this->pop();
int b = this->pop();
int c = b/a;
if (c<=0 and b!=0){
    c-=1;
}
this->push(c);
return c;
}

int* Stack_A:: get_stack(){
return stk;
}

int Stack_A:: get_size(){
return size;
}
