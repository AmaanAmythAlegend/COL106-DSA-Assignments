#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    Comp();
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int size = 0;
    int n[10] = {1, 41, 1681, 68921, 125698, 53499, 93410, 229726, 118549, 60397};
    std::vector<int> TopK;
    // Other data members and functions specific to Your implementation
};

#endif // COMP_H
