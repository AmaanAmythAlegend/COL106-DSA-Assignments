#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include "evaluator.h"
#include "ulimitedint.h"
#include "ulimitedrational.h"
#include "symtable.h"
#include "exprtreenode.h"

#define NUM_FILES 5

/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */

int fadder_sum(int x1, int x2, int c){
    int x = x1+x2+c;
    return x%10;
}

int fadder_carry(int x1, int x2, int c){
    int x = x1+x2+c;
    x/=10;
    return x;
}

int fsub_diff(int x1, int x2, int c){
    x1 = x1 + c;
    int sum = x1 - x2;
    if (sum<0){
        sum+=10;
    }
    return sum;
}

int fsub_carry(int x1, int x2, int c){
    x1 = x1 + c;
    if (x1-x2<0){
        return -1;
    }
    else{
        return 0;
    }
}

string UnlimitedInt::to_string(){
    string s;
    bool c = 1;
    for(int i = 0; i < size;i++){
        if (unlimited_int[i]!=0){
            c = 0;
        }
    }
    if (c){
        return "0";
    }
    if (sign==1){
        s = "";
        bool d = 1;
        for(int i = 0; i < size; i++){
            if(d and unlimited_int[i]!=0){
                d = 0;
            }
            if (d==0){
                s += std::to_string(unlimited_int[i]);
            }
        }
    }
    else{
        s = "-";
        for(int i = 0; i < size; i++){
            s += std::to_string(unlimited_int[i]);
        }
    }
    return s;
}

UnlimitedInt::UnlimitedInt(){
    size = 1;
    sign = 1;
    capacity = 1;
}

UnlimitedInt::UnlimitedInt(string s){
    if (s[0]=='-'){
        sign = -1;
        unlimited_int = new int[s.length()-1];
        for(int i = 0; i<s.length()-1; i++){
            unlimited_int[i] = s[i+1] - '0';
        }
    }
    else{
        sign = 1;
        unlimited_int = new int[s.length()];
        for(int i = 0; i<s.length(); i++){
            unlimited_int[i] = s[i] - '0';
        }
    }
    if (sign == 1){
        size = s.length();
    }
    else{
        size = s.length() - 1;
    }
}

UnlimitedInt::UnlimitedInt(int x){
    string s;
    s = std::to_string(x);
    if (s[0]=='-'){
        sign = -1;
        unlimited_int = new int[s.length()-1];
        for(int i = 0; i<s.length()-1; i++){
            unlimited_int[i] = s[i+1] - '0';
        }
    }
    else{
        sign = 1;
        unlimited_int = new int[s.length()];
        for(int i = 0; i<s.length(); i++){
            unlimited_int[i] = s[i] - '0';
        }
    }
    if (sign == 1){
        size = s.length();
    }
    else{
        size = s.length() - 1;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    unlimited_int = ulimited_int;
    capacity = cap;
    sign = sgn;
    size = sz;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt*i2){
    int s1 = i1->get_size();
    int s2 = i2->get_size();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();
    int si1 = i1->get_sign();
    int si2 = i2->get_sign();

    UnlimitedInt* num = new UnlimitedInt("0");
    string s, temp1, temp2;
    UnlimitedInt* m_one = new UnlimitedInt("-1");
    temp1 = i1->to_string();
    if (si1==-1){
        temp1 = temp1.substr(1, temp1.length()-1);        
    }
    UnlimitedInt* root = new UnlimitedInt(temp1);
    for(int i = 0; i < s2; i++){
        UnlimitedInt* sub = new UnlimitedInt("0");
        for (int j = 0; j < a2[s2-1-i]; j++){
            sub = add(sub, root);
        }
        temp2 = sub->to_string();
        for(int k = 0; k < i; k++){
            temp2+="0";
        }
        num = add(num, new UnlimitedInt(temp2));
    }
    if (si1*si2!=1){
        s = num->to_string();
        s = '-' + s;
        num = new UnlimitedInt(s);
        return num;
    }
    return num;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int s1 = i1->get_size();
    int s2 = i2->get_size();
    int* a1 = i1->get_array();
    int* a2 = i2->get_array();
    int si1 = i1->get_sign();
    int si2 = i2->get_sign();
    string s;
    if(si1==1 and si2==1){
        int max;
        if(s1>s2) max = s1;
        else max = s2;
        s = "";
        int sum, carry;
        carry = 0;
        for(int i = 0;i < max;i++){
            if(s2-1-i<0){
                sum = fadder_sum(a1[s1-1-i], 0, carry);
                carry = fadder_carry(a1[s1-1-i], 0, carry);
                s = std::to_string(sum) + s;
            }
            else if(s1-1-i<0){
                sum = fadder_sum(0, a2[s2-1-i], carry);
                carry = fadder_carry(0, a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
            else{
                sum = fadder_sum(a1[s1-1-i], a2[s2-1-i], carry);
                carry = fadder_carry(a1[s1-1-i], a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
        }
        if (carry!=0){
            s = '1' + s;
        }
        UnlimitedInt* num = new UnlimitedInt(s);
        return num;
    }
    else if(si1==-1 and si2==-1){
        int max;
        if(s1>s2) max = s1;
        else max = s2;
        s = "";
        int sum, carry;
        carry = 0;
        for(int i = 0;i < max;i++){
            if(s2-1-i<0){
                sum = fadder_sum(a1[s1-1-i], 0, carry);
                carry = fadder_carry(a1[s1-1-i], 0, carry);
                s = std::to_string(sum) + s;
            }
            else if(s1-1-i<0){
                sum = fadder_sum(0, a2[s2-1-i], carry);
                carry = fadder_carry(0, a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
            else{
                sum = fadder_sum(a1[s1-1-i], a2[s2-1-i], carry);
                carry = fadder_carry(a1[s1-1-i], a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
        }
        if (carry!=0){
            s = '1' + s;
        }
        s = '-' + s;
        UnlimitedInt* num = new UnlimitedInt(s);
        return num;
    }
    else if (si1==1 and si2==-1){
        int max;
        if(s1>s2) max = s1;
        else max = s2;
        s = "";
        int sum, carry;
        carry = 0;
        for(int i = 0;i < max;i++){
            if(s2-1-i<0){
                sum = fsub_diff(a1[s1-1-i], 0, carry);
                carry = fsub_carry(a1[s1-1-i], 0, carry);
                s = std::to_string(sum) + s;
            }
            else if(s1-1-i<0){
                sum = fsub_diff(0, a2[s2-1-i], carry);
                carry = fsub_carry(0, a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
            else{
                sum = fsub_diff(a1[s1-1-i], a2[s2-1-i], carry);
                carry = fsub_carry(a1[s1-1-i], a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
        }
        if (carry!=0){
            string s1 = "";
            for (long long int j = 0; j<s.length();j++){
                s1+='9';
            }
            UnlimitedInt* m_one = new UnlimitedInt("-1");
            UnlimitedInt* comp = new UnlimitedInt(s1);
            UnlimitedInt* temp = new UnlimitedInt(s);
            temp = add(temp, m_one);
            temp = mul(m_one, temp);
            temp = add(comp, temp);
            UnlimitedInt* num = mul(m_one, temp);
            return num;
        }
        else{
            UnlimitedInt* num = new UnlimitedInt(s);
            return num;
        }
    }
    else{
        a1 = i2->get_array();
        a2 = i1->get_array();
        s1 = i2->get_size();
        s2 = i1->get_size();
        int max;
        if(s1>s2) max = s1;
        else max = s2;
        s = "";
        int sum, carry;
        carry = 0;
        for(int i = 0;i < max;i++){
            if(s2-1-i<0){
                sum = fsub_diff(a1[s1-1-i], 0, carry);
                carry = fsub_carry(a1[s1-1-i], 0, carry);
                s = std::to_string(sum) + s;
            }
            else if(s1-1-i<0){
                sum = fsub_diff(0, a2[s2-1-i], carry);
                carry = fsub_carry(0, a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
            else{
                sum = fsub_diff(a1[s1-1-i], a2[s2-1-i], carry);
                carry = fsub_carry(a1[s1-1-i], a2[s2-1-i], carry);
                s = std::to_string(sum) + s;
            }
        }
        if (carry!=0){
            string s1;
            for (int j = 0; j<s.length();j++){
                s1+='9';
            }
            UnlimitedInt* m_one = new UnlimitedInt("-1");
            UnlimitedInt* comp = new UnlimitedInt(s1);
            UnlimitedInt* temp = new UnlimitedInt(s);
            temp = add(temp, m_one);
            temp = mul(m_one, temp);
            temp = add(comp, temp);
            UnlimitedInt* num = mul(m_one, temp);
            return num;
        }
        else{
            UnlimitedInt* num = new UnlimitedInt(s);
            return num;
        }
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* m_one = new UnlimitedInt("-1");
    i2 = mul(i2, m_one);
    return add(i1, i2);
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* zero = new UnlimitedInt("0");
    UnlimitedInt* one = new UnlimitedInt("1");
    UnlimitedInt* m_one = new UnlimitedInt("-1");
    if (i1->get_sign()==1 and i2->get_sign()==1){
        UnlimitedInt* factor = new UnlimitedInt("2");
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* quo1 = new UnlimitedInt("1");
        UnlimitedInt* quo2 = new UnlimitedInt("2");
        if (sub(i2,i1)->get_sign()==1){
            bool c = 1;
            UnlimitedInt* quo;
            int s = sub(i2,i1)->get_size();
            for(int i = 0;i<s;i++){
                if (sub(i2,i1)->get_array()[i]!=0){
                    c = 0;
                }
            }
            if (c){
                quo = new UnlimitedInt("1");     
            }
            else{
                quo = new UnlimitedInt("0");
            }
            return quo;
        }
        else{
            UnlimitedInt* factor = new UnlimitedInt("2");
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedInt* quo1 = new UnlimitedInt("1");
            UnlimitedInt* quo2 = new UnlimitedInt("2");
            UnlimitedInt* rem1 = sub(i1, mul(i2, quo1));
            UnlimitedInt* rem2 = sub(i1, mul(i2, quo2));
            while(!(rem2->get_sign()==-1 and rem1->get_sign()==1)){
                quo1 = quo2;
                quo2 = mul(factor, quo2);
                rem1 = sub(i1, mul(i2, quo1));
                rem2 = sub(i1, mul(i2, quo2));
            }
            UnlimitedInt* quo3 = add(quo1,one);
            rem2 = sub(i1,mul(i2,quo3));
            while(sub(quo2,quo3)->get_sign()==1 and rem2->get_sign()==1){
                quo3 = add(quo3,one);
                quo1 = add(quo1, one);
                rem1 = sub(i1, mul(i2, quo1));
                rem2 = sub(i1,mul(i2,quo3));
            }
            return quo1;
        }
        return quo1;
    }
    else if (i1->get_sign()*i2->get_sign()==-1){
        if (i1->get_sign()==-1){
            i1 = mul(m_one, i1);
        }
        else{
            i2 = mul(m_one, i2);
        }
        UnlimitedInt* zero = new UnlimitedInt("0");
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* m_one = new UnlimitedInt("-1");
        if (sub(i2,i1)->get_sign()==1){
            bool c = 1;
            UnlimitedInt* quo;
            int s = sub(i2,i1)->get_size();
            for(int i = 0;i<s;i++){
                if (sub(i2,i1)->get_array()[i]!=0){
                    c = 0;
                }
            }
            if (c){
                quo = new UnlimitedInt("-1");     
            }
            else{
                quo = new UnlimitedInt("-1");
            }
            return quo;
        }
        else{
            UnlimitedInt* factor = new UnlimitedInt("2");
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedInt* quo1 = new UnlimitedInt("1");
            UnlimitedInt* quo2 = new UnlimitedInt("2");
            UnlimitedInt* rem1 = sub(i1, mul(i2, quo1));
            UnlimitedInt* rem2 = sub(i1, mul(i2, quo2));
            while(!(rem2->get_sign()==-1 and rem1->get_sign()==1)){
                quo1 = quo2;
                quo2 = mul(factor, quo2);
                rem1 = sub(i1, mul(i2, quo1));
                rem2 = sub(i1, mul(i2, quo2));
            }
            UnlimitedInt* quo3 = add(quo1,one);
            rem2 = sub(i1,mul(i2,quo3));
            while(sub(quo2,quo3)->get_sign()==1 and rem2->get_sign()==1){
                quo3 = add(quo3,one);
                quo1 = add(quo1, one);
                rem1 = sub(i1, mul(i2, quo1));
                rem2 = sub(i1,mul(i2,quo3));
            }
            bool c = 1;
            int s = rem1->get_size();
            for(int i = 0;i<s;i++){
                if (rem1->get_array()[i]!=0){
                    c = 0;
                }
            }
            if (c){
                return mul(quo1,m_one);
            }
            else{
                return sub(mul(quo1,m_one),one);
            }
        }
    }
    else{
        i1 = mul(m_one, i1);
        i2 = mul(m_one, i2);
        UnlimitedInt* zero = new UnlimitedInt("0");
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* m_one = new UnlimitedInt("-1");
        if (sub(i2,i1)->get_sign()==1){
            bool c = 1;
            UnlimitedInt* quo;
            int s = sub(i2,i1)->get_size();
            for(int i = 0;i<s;i++){
                if (sub(i2,i1)->get_array()[i]!=0){
                    c = 0;
                }
            }
            if (c){
                quo = new UnlimitedInt("-1");     
            }
            else{
                quo = new UnlimitedInt("-1");
            }
            return quo;
        }
        else{
            UnlimitedInt* factor = new UnlimitedInt("2");
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedInt* quo1 = new UnlimitedInt("1");
            UnlimitedInt* quo2 = new UnlimitedInt("2");
            UnlimitedInt* rem1 = sub(i1, mul(i2, quo1));
            UnlimitedInt* rem2 = sub(i1, mul(i2, quo2));
            while(!(rem2->get_sign()==-1 and rem1->get_sign()==1)){
                quo1 = quo2;
                quo2 = mul(factor, quo2);
                rem1 = sub(i1, mul(i2, quo1));
                rem2 = sub(i1, mul(i2, quo2));
            }
            UnlimitedInt* quo3 = add(quo1,one);
            rem2 = sub(i1,mul(i2,quo3));
            while(sub(quo2,quo3)->get_sign()==1 and rem2->get_sign()==1){
                quo3 = add(quo3,one);
                quo1 = add(quo1, one);
                rem1 = sub(i1, mul(i2, quo1));
                rem2 = sub(i1,mul(i2,quo3));
            }
            if (rem1->to_string()!="0"){
                return mul(add(one,quo1),m_one);
            }
            else{
                return mul(quo1,m_one);
            }
        }
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    return sub(i1, mul(i2,div(i1,i2)));
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

/* int main(){
    UnlimitedInt* a = new UnlimitedInt("340");
    UnlimitedInt* b = new UnlimitedInt("400");
    UnlimitedInt* c = UnlimitedInt::sub(a,b);
    cout<<c->to_string();
    return 0;
} */

UnlimitedInt* cal_gcd(UnlimitedInt* p, UnlimitedInt* q){
    bool c = 1;
    bool e = 1;
    UnlimitedInt* temp;
    while(c){
        temp = p;
        p = q;
        q = UnlimitedInt::mod(temp,q);
        bool d = 1;
        for(int i = 0; i<q->get_size();i++){
            if (q->get_array()[i]!=0){
                d = 0;
            }
        }
        if (d){
            c = 0;
        }
    }
    return p;
}

UnlimitedRational* simplify(UnlimitedRational* f){
    UnlimitedInt* gcd = cal_gcd(f->get_p(), f->get_q());
    return new UnlimitedRational(UnlimitedInt::div(f->get_p(), gcd), UnlimitedInt::div(f->get_q(), gcd));
}

UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt("1");
    q = new UnlimitedInt("1");
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p = num;
    q = den;
    UnlimitedInt* m_one = new UnlimitedInt("-1");
    UnlimitedInt* gcd;
    if (p->get_sign()==1 and q->get_sign()==1){
        gcd = cal_gcd(p, q);
    }
    else if (p->get_sign()==-1 and q->get_sign()==1){
        gcd = cal_gcd(UnlimitedInt::mul(p,m_one), q);
    }
    else if (p->get_sign()==1 and q->get_sign()==-1){
        gcd = cal_gcd(p, UnlimitedInt::mul(q,m_one));
    }
    else{
        gcd = cal_gcd(UnlimitedInt::mul(p,m_one), UnlimitedInt::mul(q,m_one));
    }
    p = UnlimitedInt::div(p,gcd);
    q = UnlimitedInt::div(q,gcd);
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    return p->to_string() + '/' + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::add(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
    UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::sub(UnlimitedInt::mul(p1,q2),UnlimitedInt::mul(p2,q1));
    UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::mul(p1,p2);
    UnlimitedInt* den = UnlimitedInt::mul(q1,q2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* q2 = i2->get_q();

    UnlimitedInt* num = UnlimitedInt::mul(p1,q2);
    UnlimitedInt* den = UnlimitedInt::mul(q1,p2);
    UnlimitedRational*ans = new UnlimitedRational(num, den);
    return ans;
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    key = k;
    val = v;
    left = nullptr;
    right = nullptr;
}

SymEntry::SymEntry(){
    val = nullptr;
}

SymEntry::~SymEntry(){
    delete val;
}

SymbolTable::SymbolTable(){
    size = 0;
    root = nullptr;
}

SymEntry* ins(string k, UnlimitedRational* v, SymEntry* root){
    if (root==nullptr){
        root = new SymEntry(k, v);
        return root;
    }
    if(root->left==nullptr and k<root->key){
        root->left = new SymEntry(k, v);
        return root;
    }
    else if(root->right==nullptr and k>root->key){
        root->right = new SymEntry(k, v);
        return root;
    }
    else{
        if (k>root->key){
            root->right = ins(k, v, root->right);
            return root;
        }
        else{
            root->left = ins(k, v, root->left);
            return root;
        }
    }
}

void SymbolTable::insert(string k, UnlimitedRational* v){
    root = ins(k, v, root);
    size+=1;
}

SymEntry* successor(SymEntry* root){
    SymEntry* temp = root->right;
    while (temp->left!=nullptr){
        temp = root->left;
    }
    return temp;
}

SymEntry* rem(string k, SymEntry* root){
    SymEntry* temp = root;
    if (temp->key>k){
        temp->left = rem(k, temp->left);
        return temp;
    }
    else if (temp->key<k){
        temp->right = rem(k, temp->right);
        return temp;
    }
    else{
        if (temp->right==nullptr and temp->left==nullptr){
            delete temp;
            return nullptr;
        }
        else if (temp->right==nullptr and temp->left!=nullptr){
            SymEntry* temp1 = temp->left;
            delete temp;
            return temp1;
        }
        else if (temp->right!=nullptr and temp->left==nullptr){
            SymEntry* temp1 = temp->right;
            delete temp;
            return temp1;
        }
        else{
            SymEntry* temp1 = successor(temp);
            temp->key = temp1->key;
            temp->right = rem(temp1->key, temp->right);
            return temp1;
        }
    }
}

SymEntry* sea(string k, SymEntry* root){
    if (root->key == k){
        return root;
    }
    else{
        if (k>root->key){
            return sea(k, root->right);
        }
        else{
            return sea(k, root->left);
        }
    }
}

void SymbolTable::remove(string k){
    root = rem(k, root);
    size-=1;
}

UnlimitedRational* SymbolTable::search(string k){
    return sea(k,root)->val;
}

SymEntry* SymbolTable::get_root(){
    return root;
}

int SymbolTable::get_size(){
    return size;
}

SymbolTable::~SymbolTable(){
    delete root;
}

ExprTreeNode::ExprTreeNode(){
    type = "";
    val = NULL;
    left = nullptr;
    right = nullptr;
    evaluated_value = nullptr;
    id = "";    
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    left = nullptr;
    right = nullptr;
    if (t == "+"){
        type = "ADD";
    }
    else if (t == "-"){
        type = "SUB";
    }
    else if (t == "*"){
        type = "MUL";
    }
    else if (t == "/"){
        type = "DIV";
    }
    else{
        bool c = 1;
        for(int i = 0; i<t.length(); i++){
            if (t[i]-'0'>9 or t[i]-'0'<0){
                c = 0;
                if (!(i==0 and t[i]=='-')){
                    c = 0;
                }
                else{
                    c = 1;
                }
            }
        }
        if (c){
            type = "VAL";
            val = new UnlimitedRational(v, new UnlimitedInt("1"));
        }
        else if (t==":="){
            type = "ASS";
            id = t;
        }
        else{
            type = "VAR";
            id = t;
        }
    }
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    left = nullptr;
    right = nullptr;
    if (t == "+"){
        type = "ADD";
    }
    else if (t == "-"){
        type = "SUB";
    }
    else if (t == "*"){
        type = "MUL";
    }
    else if (t == "/"){
        type = "DIV";
    }
    else{
        bool c = 1;
        for(int i = 0; i<t.length(); i++){
            if (t[i]-'0'>9 or t[i]-'0'<0){
                c = 0;
                if (v->get_frac_str()!=t){
                    c = 0;
                }
                else{
                    c = 1;
                }
            }
        }
        if (c){
            type = "VAL";
            val = v;
        }
        else if (t==":="){
            type = "ASS";
            id = t;
        }
        else{
            type = "VAR";
            id = t;
        }
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
}

#include "evaluator.h"

using namespace std;

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    delete symtable;
}

ExprTreeNode* help(vector<string> code, int i, int j){
    i+=1;
    j-=1;
    if (i>j){
        bool c = 1;
        for(int k = 0; k<code[i-1].length(); k++){
            if (code[i-1][k]-'0'>9 or code[i-1][k]-'0'<0){
                c = 0;
                if (!(k==0 and code[i-1][k]=='-')){
                    c = 0;
                }
                else{
                    c = 1;
                }
            }
        }
        if (c){
            return new ExprTreeNode(code[i-1], new UnlimitedInt(code[i-1]));
        }
        else{
            return new ExprTreeNode(code[i-1], new UnlimitedInt());
        }
    }
    int k;
    ExprTreeNode* left_node;
    if (code[i]=="("){
        k = i;
        int c = 0;
        while(code[k]!=")" or c!=1){
            if (code[k]=="("){
                c+=1;
            }
            else if (code[k]==")"){
                c-=1;
            }
            k+=1;
        }
        k+=1;
        left_node = help(code, i, k);
    }
    else{
        k = i;
        k+=1;
        left_node = help(code, i, k);
    }

    ExprTreeNode* node = new ExprTreeNode(code[k], new UnlimitedInt());

    k = k+1;
    ExprTreeNode* right_node = help(code, k, j);

    node->left = left_node;
    node->right = right_node;
    return node;
}

UnlimitedRational* evaluate(ExprTreeNode* root, SymbolTable* symtable){
    if (root->type=="ADD"){
        root->evaluated_value = UnlimitedRational::add(evaluate(root->left, symtable), evaluate(root->right, symtable));
        return root->evaluated_value;
    }
    else if (root->type=="SUB"){
        root->evaluated_value = UnlimitedRational::sub(evaluate(root->left, symtable), evaluate(root->right, symtable));
        return root->evaluated_value;
    }
    else if (root->type=="MUL"){
        root->evaluated_value = UnlimitedRational::mul(evaluate(root->left,symtable), evaluate(root->right,symtable));
        return root->evaluated_value;
    }
    else if (root->type=="DIV"){
        root->evaluated_value = UnlimitedRational::div(evaluate(root->left,symtable), evaluate(root->right, symtable));
        return root->evaluated_value;
    }
    else if (root->type=="VAL"){
        root->evaluated_value = root->val;
        return root->evaluated_value;
    }
    else if (root->type=="VAR"){
        root->evaluated_value = symtable->search(root->id);
        return root->evaluated_value;
    }
    else{
        return nullptr;
    }
}

void Evaluator::parse(vector<string> code){
    ExprTreeNode* root = new ExprTreeNode(":=", new UnlimitedInt());
    root->left = new ExprTreeNode();
    root->left->type = "VAR";
    root->left->id = code[0];
    root->right = help(code, 2, code.size());
    expr_trees.push_back(root);
}

void Evaluator::eval(){
    ExprTreeNode* root = expr_trees.back();
    cout<<"1"<<root->left->id;
    root->evaluated_value = evaluate(root->right, symtable);
    cout<<"2";
    symtable->insert(root->left->id, root->evaluated_value);
    cout<<"3";
}


void checkEvalTreeBasic(ExprTreeNode *root, std::vector<std::string> &evalOutput, int &lineCount, bool &error){
    if(root == nullptr){
        error = true;
        std::cerr << "Eval tree isn't built correctly" << std::endl;
        return;
    }
    if(root->type == "VAR" || root->type == "VAL"){
        return;
    }
    checkEvalTreeBasic(root->left, evalOutput, lineCount, error);
    checkEvalTreeBasic(root->right, evalOutput, lineCount, error);
    if(root->evaluated_value->get_frac_str() != evalOutput[lineCount]){
        error = true;
        std::cerr << "Eval tree isn't built correctly" << std::endl;
        return;
    }
    lineCount++;
}

void checkParseTreeBasic(ExprTreeNode *root, std::vector<std::string> &tokenVector, bool &error, bool isMainRoot = false){
    if(root == nullptr){
        error = true;
        std::cerr << "Parse tree isn't built correctly" << std::endl;
        return;
    }
    if(isMainRoot){
        if(root->left == nullptr || root->right == nullptr){
            error = true;
            std::cerr << "Parse tree isn't built correctly at node :=" << std::endl;
            return;
        }

        checkParseTreeBasic(root->left, tokenVector, error);
        tokenVector.push_back(":=");

        const bool needsParentheses = (root->right->type != "VAR" && root->right->type != "VAL");

        if (needsParentheses) {
            tokenVector.push_back("(");
        }

        checkParseTreeBasic(root->right, tokenVector, error);

        if (needsParentheses) {
            tokenVector.push_back(")");
        }

        return;
    }

    if(root->type == "VAR"){
        tokenVector.push_back(root->id);
        return;
    }
    if(root->type == "VAL"){
        tokenVector.push_back(root->val->get_p_str());
        return;
    }
    if(root->left == nullptr || root->right == nullptr){
        error = 1;
        std::cerr << "Parse tree isn't built correctly" << std::endl;
        return;
    }

    const bool needParanthesesLeft = (root->left->type != "VAR" && root->left->type != "VAL");

    if(needParanthesesLeft) {
        tokenVector.push_back("(");
    }

    checkParseTreeBasic(root->left, tokenVector, error);

    if(needParanthesesLeft) {
        tokenVector.push_back(")");
    }

    if (root->type == "ADD") {
        tokenVector.push_back("+");
    } else if (root->type == "SUB") {
        tokenVector.push_back("-");
    } else if (root->type == "MUL") {
        tokenVector.push_back("*");
    } else if (root->type == "DIV") {
        tokenVector.push_back("/");
    } else {
        error = 1;
        std::cerr << "Invalid type detected in the parse Tree, neither of VAR, VAL, ADD, SUB, MUL, DIV FOUND "<<root->type << std::endl;
        return; 
    }
    const bool needParanthesesRight = (root->right->type != "VAR" && root->right->type != "VAL");

    if(needParanthesesRight) {
        tokenVector.push_back("(");
    }

    checkParseTreeBasic(root->right, tokenVector, error);

    if(needParanthesesRight) {
        tokenVector.push_back(")");
    }

}


int main() {
    for(int  fileNum = 1; fileNum <= NUM_FILES; fileNum++) {
        Evaluator evaluator;
        std::string filePath = "./test_cases/test_" + std::to_string(fileNum) + ".txt";

        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the file: " << filePath << std::endl;
            return 1;
        }

        
        std::string evalFilePath = "./test_cases/eval_output_" + std::to_string(fileNum) + ".txt";

        std::ifstream evalFile(evalFilePath);

        if (!evalFile.is_open()) {
            std::cerr << "Failed to open the file: " << evalFilePath << std::endl;
            return 1;
        }
        std::vector<std::string> evalOutput;
        std::string evalLine;
        while (std::getline(evalFile, evalLine)) {
            evalOutput.push_back(evalLine);
        }
        int evalCurr = 0;


        std::string line;
        std::regex tokenRegex("([a-zA-Z_][a-zA-Z0-9_]*|:=|\\(|\\)|\\+|\\-|\\*|\\/|\\d+)");
        int lineNum = 1;
        while (std::getline(inputFile, line)) {
            std::vector<std::string> tokens;
            auto words_begin = std::sregex_iterator(line.begin(), line.end(), tokenRegex);
            auto words_end = std::sregex_iterator();

            for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                tokens.push_back(i->str());
            }
            evaluator.parse(tokens);
            std::vector<std::string> tokenVector;
            bool parseError = false;
            checkParseTreeBasic(evaluator.expr_trees[evaluator.expr_trees.size() - 1], tokenVector, parseError, true);
            if(tokenVector != tokens || parseError){
                std::cerr << "Parse tree isn't built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
                return 1;
            }
            else{
                std::cout << "Parse tree built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
            }
            evaluator.eval();
            bool evalError = false;
            checkEvalTreeBasic(evaluator.expr_trees[evaluator.expr_trees.size() - 1]->right, evalOutput, evalCurr, evalError);
            if(evalError){
                std::cerr << "Eval tree isn't built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
                return 1;
            }
            else{
                std::cout << "Eval tree built correctly for line number "<< lineNum <<" in test case " <<fileNum << std::endl;
            } 
            lineNum++;
        }
        inputFile.close();
    }

    return 0;
}