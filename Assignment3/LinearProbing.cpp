#include "LinearProbing.h"

LinearProbing::LinearProbing() {
    bankStorage1d.resize(200003);
        for (int i = 0;i<200003;i++){
            Account a;
            a.id = "notreal";
            bankStorage1d[i] = a;
        }
}

void LinearProbing::createAccount(std::string id, int count) {
    int h = hash(id);
    Account a;
    a.balance = count;
    a.id = id;
    int j = h;
    while(bankStorage1d[j].id!="notreal" and bankStorage1d[j].id!="x"){
        j=(j+1)%bankStorage1d.size();
    }
    bankStorage1d[j] = a;
    size+=1;
    TopK.push_back(count);
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    std::vector<int>ans;
    for(int i = 0;i<k;i++){
        for (int j = 1;j<TopK.size();j++){
            if (TopK[j-1]>TopK[j]){
                int temp = TopK[j];
                TopK[j] = TopK[j-1];
                TopK[j-1] = temp;
            }
        }
        ans.push_back(TopK[TopK.size()-1-i]);
    }
    return ans; // Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    int j = h;
    while (bankStorage1d[j].id!=id){
        j=(j+1)%bankStorage1d.size();
    }
    return bankStorage1d[j].balance; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    int j = h;
    if (bankStorage1d[j].id==id){
        int bal = bankStorage1d[j].balance;
        bankStorage1d[j].balance+=count;
        std::vector<int>::iterator it;
        for(it = TopK.begin();it!=TopK.end();it++){
            if (*it==bal){
                *it+=count;
            }
        }
        return;
    }
    j=(j+1)%bankStorage1d.size();
    while(bankStorage1d[j].id!=id){
        if (j==h){
            this->createAccount(id,count);
            return;
        }
        j=(j+1)%bankStorage1d.size();
    }
    int bal = bankStorage1d[j].balance;
    bankStorage1d[j].balance+=count;
    std::vector<int>::iterator it;
    for(it = TopK.begin();it!=TopK.end();it++){
        if (*it==bal){
            *it+=count;
        }
    }
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    int j = h;
    if (bankStorage1d[j].id==id){
        return true;
    }
    j=(j+1)%bankStorage1d.size();
    while(bankStorage1d[j].id!=id){
        if (j==h or bankStorage1d[j].id=="notreal"){
            return false;
        }
        j=(j+1)%bankStorage1d.size();
    }
    return true; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    std::vector<int>::iterator it;
    int j = h;
    if (bankStorage1d[j].id==id){
        bankStorage1d[j].id = "x";
        int bal = bankStorage1d[j].balance;
        size-=1;
        for(it = TopK.begin();it!=TopK.end();it++){
            if (*it==bal){
                TopK.erase(it);
                break;
            }
        }
        return true;
    }
    j=(j+1)%bankStorage1d.size();
    while(bankStorage1d[j].id!=id){
        if (j==h){
            return false;
        }
        j=(j+1)%bankStorage1d.size();
    }
    bankStorage1d[j].id = "x";
    int bal = bankStorage1d[j].balance;
    size-=1;
    for(it = TopK.begin();it!=TopK.end();it++){
        if (*it==bal){
            TopK.erase(it);
            break;
        }
    }
    return true; // Placeholder return value
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int l = 0;
    for (int i = 0;i<id.size();i++){
        l+=id[i]*n[i%10];
    }
    l = l%200003;
    return l; // Placeholder return value
}
