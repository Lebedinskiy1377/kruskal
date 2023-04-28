#include "DisjointSetSystem.h"

DisjointSetSystem::DisjointSetSystem(int size) {
    p.resize(size);
    for (int i = 0; i < size; ++i)
        p[i] = i;
    r.resize(size, 1);
}

DisjointSetSystem::~DisjointSetSystem() {
    p.clear();
    r.clear();
}

int DisjointSetSystem::getRoot(int v) {
    if (p[v] == v)
        return v;
    return p[v] = getRoot(p[v]);
}

bool DisjointSetSystem::merge(int a, int b){
    int root_a = getRoot(a);
    int root_b = getRoot(b);
    if(root_a == root_b)
        return false;
    if (r[root_a] > r[root_b])
        p[root_b] = root_a;
    else if (r[root_a] < r[root_b])
        p[root_a] = root_b;
    else {
        p[root_b] = root_a;
        r[root_a]++;
    }
    return true;
}



