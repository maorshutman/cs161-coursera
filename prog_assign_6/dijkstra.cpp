
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "dijkstra.h"

void load_graph(graph& g, std::string path) {
    int u, v, len;
    std::ifstream file(path);
    std::string line;
    while (getline(file, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream is(line);        
        is >> u;
        while (is >> v >> len) { g.add_edge(u - 1, v - 1, len); }
    }
}

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    int n = atoi(argv[2]);

    graph g(n);
    load_graph(g, path);
    print_graph(g);

    std::vector<int> len(g.adj.size(), MAX);
    len[0] = 0;
    dijkstra(g, len, 0);

    int indices[10] = { 7, 37, 59, 82, 99, 115, 133 , 165, 188, 197 };
    for (int i = 0; i < 10; ++i) { std::cout << len[indices[i] - 1] << "\n"; }

    return 0;
}