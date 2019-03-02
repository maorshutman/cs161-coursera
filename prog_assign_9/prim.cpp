#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "prim.h"

int main(int argc, char *argv[]) {

	std::string path = argv[1];
	std::ifstream file(path);
	int n, m;
	file >> n >> m;
	
	graph g(n);
	int u, v, cost;
	while (file >> u >> v >> cost) {
		g.add_edge(u - 1, v - 1, cost);
	}
	print_graph(g);

	std::vector<edge> mst = prim(g);

	int sum = 0;
	for (int i = 0; i < mst.size(); ++i) {
		sum += mst[i].cost;
	}
	std::cout << mst.size() << " " <<  sum << "\n";

	return 0;
}