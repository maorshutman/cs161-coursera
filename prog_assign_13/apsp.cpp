#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include "apsp.h"

int add(int x, int y) {
    if (x > 0 && y > 0) {
        if (INT_MAX - x <= y) { return INT_MAX; }
    } else {
        return x + y;
    }
}

bool 
bellman_ford(std::vector<edge>& edges,
             std::vector<int>& vertices,
             int s) {
    int u, v, w;
    for (int i = 0; i < vertices.size() - 1; ++i) {
        for (int j = 0; j < edges.size(); ++j) {
            u = edges[j].u; v = edges[j].v; w = edges[j].weight;
            if (vertices[v] > add(vertices[u], w)) {
                vertices[v] = add(vertices[u], w);
            }
        }
    }
    for (int j = 0; j < edges.size(); ++j) {
        u = edges[j].u; v = edges[j].v; w = edges[j].weight;
        if (vertices[v] > add(vertices[u], w)) { return false; }
    }
    return true;
}

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    std::ifstream file(path);
    int n, m;
    file >> n >> m;

    std::vector<edge> edges;
    int u, v, weight;
    while (file >> u >> v >> weight) {
        edges.push_back(edge(u - 1, v - 1, weight));
    }

    // Add s.
    for (int i = 0; i < n; ++i) {
        edges.push_back(edge(n, i, 0));
    }

    std::vector<int> vertices(n + 1);
    vertices[n] = 0;
    for (int i = 0; i < n; ++i) { vertices[i] = INT_MAX; }

    // Run Bellman-Ford on the modified graph.
    bool bf = bellman_ford(edges, vertices, n);
    std::cout << "Cycles: " << bf << "\n";

    int len = INT_MAX;
    for (int i = 0; i < vertices.size(); ++i) {
        if (vertices[i] < len) { len = vertices[i]; }
    }
    std::cout << "Shortest path length: " << len << "\n";

    return 0;
}












