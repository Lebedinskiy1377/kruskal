#include "gr.h"

#pragma once

using std::vector;
using std::pair;

class AdjancentMatrixGraph : public Graph {
    int v_count;
    vector<vector<int>> g;
    
public:
    AdjancentMatrixGraph(int v_count);
    ~AdjancentMatrixGraph();
    
    void insert(int v, int w, int weight = 1);
    void remove(int v, int w);
    void clear();
    vector<pair<int, int>> adjacent_vertices(int v);
    int  getSize();
    vector<Edge> getEdges();
};
