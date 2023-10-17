#include "Chaining.h"

Chaining::Chaining() {
    std::vector<std::vector<Account>> s(200003);
    bankStorage2d=s;
}

void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    Account a;
    a.balance = count;
    a.id = id;
    bankStorage2d[h].push_back(a);
    size+=1;
    TopK.push_back(count);
}

std::vector<int> Chaining::getTopK(int k) {
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

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    for(auto x:bankStorage2d[h]){
        if (x.id == id){
            return x.balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    int bal;
    int h = hash(id);
    bool t = false;
    for(int i = 0;i<bankStorage2d[h].size();i++){
        if (bankStorage2d[h][i].id == id){
            bal = bankStorage2d[h][i].balance;
            bankStorage2d[h][i].balance+=count;
            t = true;
            break;
        }
    }
    if (t==false){
        this->createAccount(id,count);
    }
    else{
    std::vector<int>::iterator it;
    for(it = TopK.begin();it!=TopK.end();it++){
        if (*it==bal){
            *it+=count;
        }
    }
    }
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    for(int i = 0;i<bankStorage2d[h].size();i++){
        if (bankStorage2d[h][i].id == id){
            return true;
        }
    }
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h = hash(id);
    std::vector<Account>::iterator it;
    std::vector<int>::iterator it1;
    for(int i = 0;i < bankStorage2d[h].size();i++){
        if (bankStorage2d[h][i].id == id){
            int bal = bankStorage2d[h][i].balance;
            bankStorage2d[h].erase(bankStorage2d[h].begin()+i);
            for(int j = 0;j < TopK.size();j++){
                if (TopK[j]==bal){
                    TopK.erase(TopK.begin() + j);
                    break;
                }
            }
            size-=1;
            return true;
        }

    }
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    int l = 0;
    for (int i = 0;i<id.size();i++){
        l+=id[i]*n[i%10];
    }
    l = l%200003;
    return l; // Placeholder return value
}

