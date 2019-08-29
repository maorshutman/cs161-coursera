#include <stdint.h>
#include <vector>
#include <set>
#include <queue> 

struct vertex {
    int v, cost;
    vertex (int v, int cost) : v(v), cost(cost) {}
};

struct graph {
    std::vector<std::vector<vertex>> adj;
    
    graph (int n) {
        for (int i = 0; i < n; ++i) {
            adj.push_back(std::vector<vertex>());
        }
    }

    void add_edge(int u, int v, int cost) {
        adj[u].push_back(vertex(v, cost));
        adj[v].push_back(vertex(u, cost));
    }
};

struct edge {
    int u, v, cost;
    edge(int u, int v, int cost) : u(u), v(v), cost(cost) {}
};

bool operator<(const edge& x, const edge& y) {
    return x.cost > y.cost;
}

void find_edges(graph& g,
                std::set<int>& s,
                std::priority_queue<edge>& pq, 
                int v) {
    int w;
    for (int j = 0; j < g.adj[v].size(); ++j) {
        w = g.adj[v][j].v;
        if (!s.count(w)) {
            pq.push(edge(v, w, g.adj[v][j].cost));
        }
    }
}

std::vector<edge> prim(graph& g) {
    int n = g.adj.size();
    std::vector<edge> T;
    std::set<int> X{0};
    std::priority_queue<edge> pq;
    find_edges(g, X, pq, 0);

    int v;
    while (X.size() != n) {
        v = pq.top().v;

        if (X.count(v)) {
            pq.pop();       
            continue;
        }

        T.push_back(pq.top());      
        X.insert(v);
        pq.pop();
        find_edges(g, X, pq, v);
    }

    return T;
}

void print_graph(graph& g) {
    for (int i = 0; i < g.adj.size(); ++i) {
        std::cout << i + 1 << " -> ";
        for (int j = 0; j < g.adj[i].size(); ++j) {
            std::cout << "(" << g.adj[i][j].v + 1 << ", " << g.adj[i][j].cost << ")" << " ";
        }
        std::cout << "\n";
    }
}
