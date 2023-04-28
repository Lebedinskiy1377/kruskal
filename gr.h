#include <vector>
#include "Edge.h"
#pragma once

using std::vector;
using std::pair;

class Graph {
    
public:
    virtual void insert(int v, int w, int weight = 1) = 0;
    virtual void remove(int v, int w) = 0;
    virtual void clear() = 0;
    virtual vector<pair<int, int>> adjacent_vertices(int v) = 0; //вектор хранит пары содержащие вершину и вес
    virtual int getSize() = 0;
    virtual vector<Edge> getEdges() = 0;
};
