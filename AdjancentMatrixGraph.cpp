#include "AdjancentMatrixGraph.h"

using std::make_pair;

AdjancentMatrixGraph::AdjancentMatrixGraph(int v_count)
{
    g.resize(v_count);
    for(int i = 0; i < v_count; ++i)
        g[i].resize(v_count);
    this->v_count = v_count;
}

AdjancentMatrixGraph::~AdjancentMatrixGraph() {
    clear();
}

void AdjancentMatrixGraph::insert(int v, int w, int weight)
{
    if (v >= v_count || w >= v_count)
    {
        v_count = (v > w ? v : w) + 1;
        g.resize(v_count);
        for(int i = 0; i < v_count; ++i)
            g[i].resize(v_count);
    }
    g[v][w] = weight;
    g[w][v] = weight;
}

void AdjancentMatrixGraph::remove(int v, int w){
    if (v >= v_count || w >= v_count){
        return;
    }
    g[v][w] = 0;
    g[w][v] = 0;
}

void AdjancentMatrixGraph::clear(){
    for(int i = 0; i < v_count; i++){
        g[i].clear();
    }
    g.clear();
    v_count = 0;
}

vector<pair<int, int>> AdjancentMatrixGraph::adjacent_vertices(int v) {
    vector<pair<int, int>> vec;
    if (v >= v_count)
        return vec;
    
    for (int i = 0; i < v_count; ++i) {
        if (g[v][i] != 0){
            vec.push_back(make_pair(i, g[v][i]));
        }
    }
    return vec;
}

int AdjancentMatrixGraph::getSize() {
    return v_count;
}

vector<Edge> AdjancentMatrixGraph::getEdges(){
    vector<Edge> edges;
    for (int i = 0; i < this->v_count; ++i) 
        for (int j = i; j < this->v_count; ++j)
            if (g[i][j] != 0) {
                Edge ed;
                ed.a = i;
                ed.b = j;
                ed.weight = g[i][j];
                edges.push_back(ed);
            }
    return edges;
}



