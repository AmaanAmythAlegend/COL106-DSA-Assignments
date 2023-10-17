#include "CubicProbing.h"

CubicProbing::CubicProbing() {
    bankStorage1d.resize(300007);
        for (int i = 0;i<300007;i++){
            Account a;
            a.id = "notreal";
            bankStorage1d[i] = a;
        }
}

void CubicProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    Account a;
    a.balance = count;
    a.id = id;
    int j = h;
    int k = 1;
    while(bankStorage1d[j].id!="notreal" and bankStorage1d[j].id!="x"){
        j=(h+(k*k*k))%bankStorage1d.size();
        k+=1;
    }
    bankStorage1d[j] = a;
    size+=1;
    TopK.push_back(count);
}

std::vector<int> CubicProbing::getTopK(int k) {
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

int CubicProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    int j = h;
    int k = 1;
    while (bankStorage1d[j].id!=id){
        j=(h+(k*k*k))%bankStorage1d.size();
        k+=1;
    }
    return bankStorage1d[j].balance; // Placeholder return value
}

void CubicProbing::addTransaction(std::string id, int count) {
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
    int k = 2;
    while(bankStorage1d[j].id!=id){
        if (j==h){
            this->createAccount(id,count);
            return;
        }
        j=(h+(k*k*k))%bankStorage1d.size();
        k+=1;
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

bool CubicProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    int j = h;
    if (bankStorage1d[j].id==id){
        return true;
    }
    j=(j+1)%bankStorage1d.size();
    int k = 2;
    while(bankStorage1d[j].id!=id){
        if (bankStorage1d[j].id=="notreal"){
            return false;
        }
        j=(h+(k*k*k))%bankStorage1d.size();
    }
    return true; // Placeholder return value
}

bool CubicProbing::deleteAccount(std::string id) {
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
    int k = 2;
    while(bankStorage1d[j].id!=id){
        if (j==h){
            return false;
        }
        j=(h+(k*k*k))%bankStorage1d.size();
        k+=1;
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
int CubicProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int CubicProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int l = 0;
    for (int i = 0;i<id.size();i++){
        l+=id[i]*n[i%10];
    }
    l = l%300007;
    return l; // Placeholder return value
}
