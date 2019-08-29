#include <vector>

struct edge {
    int u, v, weight;
    edge(int u, int v, int weight):
    u(u), v(v), weight(weight) {}
};

void print_edges(std::vector<edge>& edges) {
    for (int i = 0; i < edges.size(); ++i) {
        std::cout << edges[i].u << " " << edges[i].v << " " << edges[i].weight << "\n";
    }
}
