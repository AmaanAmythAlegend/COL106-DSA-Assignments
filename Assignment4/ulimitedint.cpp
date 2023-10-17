/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

using namespace std;

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
    int* a2 = i2->get_array();
    int si1 = i1->get_sign();
    int si2 = i2->get_sign();

    UnlimitedInt* num = new UnlimitedInt("0");
    string s, temp1, temp2;
    temp1 = i1->to_string();
    if (si1==-1){
        temp1 = temp1.substr(1, temp1.length()-1);        
    }
    UnlimitedInt* root = new UnlimitedInt(temp1);
    UnlimitedInt* subb;
    for(int i = 0; i < s2; i++){
        subb = new UnlimitedInt("0");
        for (int j = 0; j < a2[s2-1-i]; j++){
            subb = add(subb, root);
        }
        temp2 = subb->to_string();
        for(int k = 0; k < i; k++){
            temp2+="0";
        }
        num = add(num, new UnlimitedInt(temp2));
    }
    delete subb;
    delete root;
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
            UnlimitedInt* temp2 = add(temp, m_one);
            delete temp;
            UnlimitedInt* temp3 = mul(m_one, temp2);
            delete temp2;
            UnlimitedInt* temp4 = add(comp, temp3);
            delete temp3;
            UnlimitedInt* num = mul(m_one, temp4);
            delete m_one;
            delete temp4;
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
            UnlimitedInt* temp2 = add(temp, m_one);
            delete temp;
            UnlimitedInt* temp3 = mul(m_one, temp2);
            delete temp2;
            UnlimitedInt* temp4 = add(comp, temp3);
            delete temp3;
            UnlimitedInt* num = mul(m_one, temp4);
            delete m_one;
            delete temp4;
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
    UnlimitedInt* temp = mul(i2, m_one);
    delete m_one;
    UnlimitedInt* ans = add(i1, temp);
    delete temp;
    return ans;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    string quo = "";
    UnlimitedInt* m_one = new UnlimitedInt("-1");
    UnlimitedInt* ii1;
    UnlimitedInt* ii2;
    if (i1->get_sign()==-1){
        UnlimitedInt* garb = new UnlimitedInt(i1->to_string());
        ii1 = mul(m_one, garb);
        delete garb;
    }
    else{
        ii1 = new UnlimitedInt(i1->to_string());
    }
    if (i2->get_sign()==-1){
        UnlimitedInt* garb1 = new UnlimitedInt(i2->to_string());
        ii2 = mul(m_one, garb1);
        delete garb1;
    }
    else{
        ii2 = new UnlimitedInt(i2->to_string());
    }
    int s1 = ii1->to_string().length();
    int s2 = ii2->to_string().length();
    
    int si1 = i1->get_sign();
    int si2 = i2->get_sign();

    if(s1<s2){
        if (si1*si2==-1){
            delete m_one;
            return new UnlimitedInt("-1");
        }
        else{
            delete m_one;
            return new UnlimitedInt("0");
        }
    }
    else if(s1==s2){
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* quo1 = new UnlimitedInt("0");
        UnlimitedInt* quo2 = new UnlimitedInt("1");
        UnlimitedInt* temp = sub(ii1, ii2);
        if (temp->get_sign()==-1){
            if(si1*si2==-1){
                delete one;
                delete quo1;
                delete quo2;
                delete temp;
                return m_one;
            }
            else{
                delete m_one;
                delete one;
                delete quo2;
                delete temp;
                return quo1;
            }
        }
        quo1 = add(quo1, one);
        quo2 = add(quo2, one);
        UnlimitedInt* temp24 = mul(ii2, quo1);
        UnlimitedInt* temp25 = mul(ii2, quo2);
        UnlimitedInt* temp4 = sub(ii1, temp24);
        UnlimitedInt* temp5 = sub(ii1, temp25);
        delete temp24;
        delete temp25;
        UnlimitedInt* temp26;
        UnlimitedInt* temp27;
        while(temp4->get_sign()!=1 or temp5->get_sign()!=-1){
            quo1 = add(quo1, one);
            quo2 = add(quo2, one);
            temp24 = mul(ii2, quo1);
            temp25 = mul(ii2, quo2);
            temp4 = sub(ii1, temp24);
            temp5 = sub(ii1, temp25);
            delete temp24;
            delete temp25;
        }
        delete temp4;
        delete temp5;
        if (si1*si2==-1){
            UnlimitedInt* ans;
            UnlimitedInt* temp8 = mul(quo1, ii2);
            UnlimitedInt* temp9 = sub(ii1, temp8);
            delete temp8;
            if (temp9->to_string()=="0"){
                ans = mul(m_one, quo1);
            }
            else{
                UnlimitedInt* temp10 = mul(m_one, quo1);
                ans = add(temp10, m_one);
                delete temp10;
            }
            delete temp9;
            delete m_one;
            delete one;
            return ans;
        }
        else{
            delete m_one;
            delete one;
            return quo1;
        }
    }
    else{
        UnlimitedInt* fac = new UnlimitedInt("10");
        UnlimitedInt* temp1 = sub(ii1, mul(fac, ii2));
        delete fac;
        if (temp1->get_sign()==-1){
            UnlimitedInt* one = new UnlimitedInt("1");
            UnlimitedInt* quo1 = new UnlimitedInt("1");
            UnlimitedInt* quo2 = new UnlimitedInt("2");
            UnlimitedInt* temp22 = mul(ii2, quo1);
            UnlimitedInt* temp23 = mul(ii2, quo2);
            UnlimitedInt* temp4 = sub(ii1, temp22);
            UnlimitedInt* temp5 = sub(ii1, temp23);
            delete temp22;
            delete temp23;
            UnlimitedInt* temp20;
            UnlimitedInt* temp21;
            while(temp4->get_sign()!=1 or temp5->get_sign()!=-1){
                quo1 = add(quo1, one);
                quo2 = add(quo2, one);
                temp20 = mul(ii2, quo1);
                temp4 = sub(ii1, temp20);
                temp21 = mul(ii2, quo2);
                temp5 = sub(ii1, temp21);
            }
            delete temp4;
            delete temp20;
            delete temp21;
            delete temp5;
            if (si1*si2==-1){
                UnlimitedInt* ans;
                UnlimitedInt* temp8 = sub(ii1, mul(ii2, quo1));
                if (temp8->to_string()=="0"){
                    ans = mul(m_one, quo1);
                }
                else{
                    UnlimitedInt* temp9 = mul(m_one, quo1);
                    ans = add(temp9, m_one);
                    delete temp9;
                }
                delete temp8;
                delete temp1;
                delete m_one;
                delete one;
                return ans;
            }
            else{
                delete m_one;
                delete one;
                delete temp1;
                return quo1;
            }
        }
        else{
            delete temp1;
        }
        UnlimitedInt* rem = ii1;
        UnlimitedInt* temp10;
        UnlimitedInt* temp12;
        UnlimitedInt* temp11;
        UnlimitedInt* ten = new UnlimitedInt(10);
        UnlimitedInt* one = new UnlimitedInt("1");
        for (int i = s1-s2;i>-1;i--){
            temp10 = ii2;
            for (int j = 0; j<i; j++){
                temp11 = mul(temp10, ten);
                temp10 = temp11;
            }
            temp12 = div(rem, temp10);
            quo = quo + temp12->to_string();
            UnlimitedInt* temp3 = mul(temp10, temp12);
            rem = sub(rem, temp3);
        }
        delete temp10;
        delete temp11;
        delete temp12;
        delete ten;
        delete rem;
        UnlimitedInt* final = new UnlimitedInt(quo);
        if (si1*si2==-1){
            UnlimitedInt* ans;
            UnlimitedInt* temp13 = mul(m_one, final);
            UnlimitedInt* temp14 = sub(ii1,temp13);
            delete temp13;
            if (temp14->to_string()=="0"){
                ans = mul(m_one, final);
            }
            else{
                UnlimitedInt* temp15 = mul(m_one, final);
                ans = add(temp15, m_one);
                delete temp15;
            }
            delete temp14;
            delete m_one;
            delete one;
            return ans;
        }
        else{
            delete m_one;
            delete one;
            return final;
        }
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* temp1 = div(i1, i2);
    UnlimitedInt* temp2 = mul(i2, temp1);
    delete temp1;
    UnlimitedInt* temp3 = sub(i1,temp2);
    delete temp2;
    return temp3;
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}
