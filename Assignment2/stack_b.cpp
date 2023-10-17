#include "stack_b.h"
#include <iostream>
#include <stdexcept>
using namespace std;

Stack_B::Stack_B(){
size = 0;
capacity = 1024;
try{
stk = new int[capacity];
}
catch(...){
throw runtime_error("Out of Memory");
}
}

Stack_B::~Stack_B(){
delete[] stk;
}


void Stack_B:: push(int n){
if (size==capacity){
try{
int *temp = new int[capacity*2];
for (int i = 0; i<size;i++){
temp[i] = stk[i];
}
delete[] stk;
stk = temp;
capacity*=2;
stk[size] = n;
size+=1;
}
catch(...){
throw runtime_error("Out of Memory");
}

}
else{
stk[size] = n;
size+=1;
}
}

int Stack_B:: pop(){
if (size==0){
throw runtime_error("Empty Stack");
}

int r = stk[size-1];
size-=1;
if (size <= capacity/2 and capacity>=2048){
try{
int *temp = new int[capacity/2];
for (int i = 0;i<size;i++){
temp[i] = stk[i];
}
delete[] stk;
stk = temp;
capacity/=2;
}
catch(...){
throw runtime_error("Out of Memory");
}

}
return r;
}

int Stack_B:: get_element_from_top(int idx){
if (size-idx<1){
throw runtime_error("Index out of range");
}
return stk[size-idx-1];
}

int Stack_B:: get_element_from_bottom(int idx){
if (size-idx<1){
throw runtime_error("Index out of range");
}
return stk[idx];
}

int Stack_B:: add(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
int a = this->pop();
int b = this->pop();
this->push(a+b);
return a+b;
}

int Stack_B:: subtract(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
int a = this->pop();
int b = this->pop();
this->push(-a+b);
return -a+b;
}

int Stack_B:: multiply(){
if (size<2){
throw runtime_error("Not Enough Arguments");
}
int a = this->pop();
int b = this->pop();
this->push(a*b);
return a*b;
}

int Stack_B:: divide(){
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

int* Stack_B:: get_stack(){
return stk;
}

int Stack_B:: get_size(){
return size;
}
