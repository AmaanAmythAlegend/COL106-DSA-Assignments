#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    Chaining();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int n[10] = {1, 41, 1681, 68921, 25719, 54464, 32991, 152613, 57040, 138607};
    int size = 0;
    std::vector<int> TopK;
    
    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H
