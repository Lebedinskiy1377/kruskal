#include "AdjancentMatrixGraph.h"
#include "DisjointSetSystem.h"
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <set>

using std::queue;
using std::stack;
using std::string;
using std::set;
using std::make_pair;

void DFS(Graph*& g, int start);
void DFS_rec(Graph*& g, int vertex);
void DFS_rec(Graph*& g, int vertex, vector<bool>& isVisited);
void BFS(Graph*& g, int start);
int countPaperList();
void sort_bubble(vector<Edge>& edges);

bool has_loop(Graph*& g, int v);
bool has_loop(Graph*& g, int v, vector<bool>& isVisited, int p = -1);

Graph* makeGraph();
set<pair<int, int>> kruskal(Graph* g);

int main(int argc, const char * argv[]) {
    Graph* matrix = new AdjancentMatrixGraph(8);
    matrix->insert(0, 1);
    matrix->insert(0, 2);
    matrix->insert(0, 7, 2);
    matrix->insert(0, 5);
    matrix->insert(0, 6);
    matrix->insert(1, 7);
    matrix->insert(2, 7);
    matrix->insert(7, 4, 4);
    matrix->insert(4, 3);
    matrix->insert(4, 6);
    matrix->insert(4, 5, 6);
    matrix->insert(3, 5);

    /*/auto vec = matrix->getEdges();
    sort_bubble(vec);
    for (auto& it : vec)
        std::cout << it.a << ' ' << it.b << ' ' << it.weight << '\n';*/
    vector<bool> used;
    auto ost_tree = kruskal(makeGraph());
    for (auto& edge : ost_tree)
        std::cout << edge.first << ' ' << edge.second << '\n';
    
    //std::cout << has_loop(matrix, 0);
    //DFS_rec(matrix, 0);
    //std::cout << "\n";
    //DFS(matrix, 0);
    
    //BFS(matrix, 0);
    
    //std::cout << countPaperList() << "\n";
    
    return 0;
}

bool has_loop(Graph*& g, int v, vector<bool>& isVisited, int p) {
    isVisited[v] = 1;
    vector<pair<int, int>> av = g->adjacent_vertices(v);
    
    for(auto& vert: av)
    {
        int currentVertex = vert.first;
        if(!isVisited[currentVertex])
            return has_loop(g, currentVertex, isVisited, v);
        else if (currentVertex != p)
            return 1;
    }
    return 0;
}

bool has_loop(Graph*& g, int v) {
    vector<bool> isVisited(g->getSize());
    return has_loop(g, v, isVisited);
}


int hash(int i, int j, int n)
{
    return n * i + j;
}

int countPaperList(){
    Graph *g = new AdjancentMatrixGraph(1);
    const int m = 5;
    const int n = 10;
    
    vector<string> paper;
    paper.resize(m);
    paper[0] = "##..#####.";  //0 - 9
    paper[1] = ".#.#.#....";  //10 - 19
    paper[2] = "###..##.#.";
    paper[3] = "..##.....#";
    paper[4] = ".###.#####";  //n * i + j
    
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
        {
            char current = paper[i][j];
            if (current == '#')
            {
                char left = j > 0 ? paper[i][j - 1] : '/';
                char right = j < n - 1 ? paper[i][j + 1] : '/';
                char bottom = i < m - 1 ? paper[i + 1][j] : '/';
                char top = i > 0 ? paper[i - 1][j] : '/';
                
                if (left == '#')
                    g->insert(hash(i, j, n), hash(i, j - 1, n));
                if (right == '#')
                    g->insert(hash(i, j, n), hash(i, j + 1, n));
                if (bottom == '#')
                        g->insert(hash(i, j, n), hash(i + 1, j, n));
                if (top == '#')
                    g->insert(hash(i, j, n), hash(i - 1, j, n));
            }
        }
    
    int componentCount = 0;
    vector<bool> isVisited(n * m);
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
        {
            int index = hash(i, j, n);
            if (paper[i][j] == '#' && !isVisited[index])
            {
                DFS_rec(g, index, isVisited);
                ++componentCount;
            }
        }
    
    return componentCount;
}

void DFS(Graph*& g, int start) {
    stack<int> s;
    vector<bool> visited(g->getSize());
    
    s.push(start);
    
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        
        if (!visited[current]) {
            std::cout << current << '\n';
            visited[current] = true;
        
            vector<pair<int, int>> adjacentVertices = g->adjacent_vertices(current);
            for (auto vertex : adjacentVertices) {
                int v = vertex.first;
                if (!visited[v]) {
                    s.push(v);
                }
            }
        }
    }
}

void DFS_rec(Graph*& g, int vertex, vector<bool>& isVisited) {
    //std::cout << vertex << "\n";
    isVisited[vertex] = 1;
    
    vector<pair<int, int>> av = g->adjacent_vertices(vertex);
    for(auto v: av)
    {
        int currentVertex = v.first;
        if(!isVisited[currentVertex])
            DFS_rec(g, currentVertex, isVisited);
    }
}

void DFS_rec(Graph*& g, int vertex) {
    vector<bool> isVisited(g->getSize());
    DFS_rec(g, vertex, isVisited);
}

void BFS(Graph*& g, int start) {
    queue<int> q;
    vector<bool> visited(g->getSize());
    
    q.push(start);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (!visited[current]) {
            std::cout << current << '\n';
            visited[current] = true;
            
            vector<pair<int, int>> adjacentVertices = g->adjacent_vertices(current);
            for (auto vertex : adjacentVertices) {
                int v = vertex.first;
                if (!visited[v]) {
                    q.push(v);
                }
            }
        }
    }
}

Graph* makeGraph(){
    Graph* g = new AdjancentMatrixGraph(7);
    g->insert(1, 2, 6);
    g->insert(1, 3, 1);
    g->insert(1, 4, 5);
    g->insert(2, 3, 5);
    g->insert(3, 4, 5);
    g->insert(2, 5, 3);
    g->insert(3, 5, 6);
    g->insert(3, 6, 4);
    g->insert(4, 6, 2);
    g->insert(5, 6, 6);
    return g;
}

set<pair<int, int>> kruskal(Graph* g) {
    set<pair<int, int>> T;
    DisjointSetSystem dss(g->getSize());
    auto edges = g->getEdges();
    sort_bubble(edges);
    for (int i = 0; i < g->getSize(); ++i) {
        if (dss.getRoot(edges[i].a) != dss.getRoot(edges[i].b)) {
            T.insert(make_pair(edges[i].a, edges[i].b));
            dss.merge(edges[i].a, edges[i].b);
        }
    }
    return T;
}

void sort_bubble(vector<Edge>& edges) {
    for (int i = 0; i < edges.size() - 1; ++i)
        for (int j = i; j < edges.size(); ++j)
            if (edges[j].weight < edges[i].weight)
                std::swap(edges[i], edges[j]);
}