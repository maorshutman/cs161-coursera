#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "scc.h"

void load_graph(graph* g, std::string path, bool reversed) {
    int u, v;
    std::ifstream file(path);
    std::string line;
    while (getline(file, line)) {
        std::istringstream is(line);
        is >> u >> v;
        if (reversed) { g->add_edge(v - 1, u - 1); }
        else { g->add_edge(u - 1, v - 1); }
    }
}

int main(int argc, char* argv[]) {
    std::string path = argv[1];
    int n = atoi(argv[2]);

    // Build reversed graph.
    graph* g = new graph(n);
    load_graph(g, path, 1);
    print_graph(g);

    // 1st DFS loop.
    std::vector<int> f(n);
    dfs_1st_loop(g, n, f);

    std::cout << "o~oo~oo~oo~oo~o" << "\n";
    for (int i = 0; i < f.size(); ++i) {
        std::cout << f[i] + 1 << "\n";
    }

    // Rebuild graph with unreversed edges.
    delete g;
    g = new graph(n);
    load_graph(g, path, 0);
    print_graph(g);

    // 2nd DFS loop.
    std::vector<int> leader(n);
    dfs_2nd_loop(g, n, f, leader);
    
    std::cout << "o~oo~oo~oo~oo~o" << "\n";
    for (int i = 0; i < leader.size(); ++i) {
        std::cout << leader[i] << "\n";
    }

    // Count SCCs.
    std::vector<int> scc_counter(n);
    for (int i = 0; i < leader.size(); ++i) {
        scc_counter[leader[i]]++;
    }
    std::sort(scc_counter.begin(), scc_counter.end());
    std::cout << "SCC sizes: " << "\n";
    for (int i = 0; i < scc_counter.size(); ++i) {
        std::cout << scc_counter[i] << "\n";
    }

    return 0;
}
