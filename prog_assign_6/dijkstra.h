#include <stdint.h>
#include <vector>
#include <set>

#define MAX 1000000

struct vertex {
    int v, len;
    vertex (int v, int len) : v(v), len(len) {}
};

struct graph {
    std::vector<std::vector<vertex>> adj;
    
    graph (int n) {
        for (int i = 0; i < n; ++i) {
            adj.push_back(std::vector<vertex>());
        }
    }

    void add_edge(int u, int v, int len) {
        adj[u].push_back(vertex(v, len));
    }
};

struct edge {
    int v, w, len;
    edge(int v, int w, int len) : v(v), w(w), len(len) {}
};

void find_edges(graph& g,
                                std::set<int>& s, 
                                std::vector<edge>& edges) {
    edges.clear();
    int v, w, len;
    for (auto it = s.begin(); it != s.end(); ++it) {
    v = *it;
    for (int j = 0; j < g.adj[v].size(); ++j) {
        w = g.adj[v][j].v;
        len = g.adj[v][j].len;
        if (!s.count(w)) { 
            edges.push_back(edge(v, w, len));
        }
    } 
  }
}

void dijkstra(graph& g, std::vector<int>& len, int s) {
    std::set<int> X{s};
    std::vector<edge> edges;

    find_edges(g, X, edges);

    int w, l, min_l;
    while (edges.size() != 0) {
        min_l = MAX;
        for (int i = 0; i < edges.size(); ++i) {            
            l = len[edges[i].v] + edges[i].len;
            if (l <= min_l) {
                min_l = l;
                w = edges[i].w;
            }
        }
        len[w] = min_l;
        X.insert(w);
        find_edges(g, X, edges);
    }
}

void print_graph(graph& g) {
    for (int i = 0; i < g.adj.size(); ++i) {
        std::cout << i + 1 << " -> ";
        for (int j = 0; j < g.adj[i].size(); ++j) {
            std::cout << "(" << g.adj[i][j].v + 1 << ", " << g.adj[i][j].len << ")" << " ";
        }
        std::cout << "\n";
    }
}
