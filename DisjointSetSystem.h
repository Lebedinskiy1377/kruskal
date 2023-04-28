#pragma once

#include <vector>

class DisjointSetSystem {
private:
    std::vector<int> p;
    std::vector<int> r;
    
public:
    DisjointSetSystem(int size);
    ~DisjointSetSystem();
    
    int getRoot(int v);
    bool merge(int a, int b);
};
