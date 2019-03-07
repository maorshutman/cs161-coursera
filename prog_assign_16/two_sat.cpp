#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "scc.h"

int idx(int u) {
	if (u > 0) { return 2 * (u - 1); }
	return 2 * ((-u) - 1) + 1;
}

void build_impl_graph(graph* g,
				 std::vector<std::vector<int>>& clauses,
				 bool reversed) {
	int u, v;
	int u_idx, v_idx, u_not_idx, v_not_idx;
	for (int i = 0; i < clauses.size(); ++i) {
		u = clauses[i][0]; v = clauses[i][1];
		
		u_idx = idx(u);
		u_not_idx = idx(-u);
		v_idx = idx(v);
		v_not_idx = idx(-v);

		if (reversed) {
			g->add_edge(v_idx, u_not_idx);
			g->add_edge(u_idx, v_not_idx);
		} else {
			g->add_edge(u_not_idx, v_idx);
			g->add_edge(v_not_idx, u_idx);
		}
	}
}


int main(int argc, char *argv[]) {
	std::string filepath = argv[1];
	
	std::ifstream file(filepath);
	int n;
	file >> n;
	std::vector<std::vector<int>> clauses(n);

	int x, y, i = 0;
	while (file >> x >> y) {
		clauses[i].push_back(x);
		clauses[i].push_back(y);
		i++;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << clauses[i][0] << " " << clauses[i][1] << "\n";
	}
	std::cout << "o~oo~oo~oo~oo~o" << "\n";
	
	// Build the implication graph.
	graph* g = new graph(2 * n);
	build_impl_graph(g, clauses, 1);
	print_graph(g);

	// 1st DFS loop.
	std::vector<int> f(2 * n);
	dfs_1st_loop(g, 2 * n, f);
	
	// Rebuild graph with unreversed edges.
	delete g;
	g = new graph(2 * n);
	build_impl_graph(g, clauses, 0);
 	print_graph(g);

	// 2nd DFS loop.
	std::vector<int> leader(2 * n);
	dfs_2nd_loop(g, 2 * n, f, leader);

	std::cout << "o~oo~oo~oo~oo~o" << "\n";
	for (int i = 0; i < leader.size(); ++i) {
		std::cout << leader[i] << "\n";
	}

	// Number of SCCs.
	int n_scc = *std::max_element(leader.begin(), leader.end()) + 1;
	std::cout << "Number of SCCs: " <<  n_scc << "\n";

	std::vector<std::unordered_set<int>> scc_set(n_scc);
	for (int i = 0; i < n_scc; ++i) { scc_set[leader[i]].insert(i); }

	// Check if for some x, !x is in the same SCC as x. 
	int x_not;
	bool sat = true;
	for (int i = 0; i < n_scc; ++i) {
		for(auto x : scc_set[i]) {
			if (x % 2 == 0) { x_not = x + 1; }
			else { x_not = x - 1; }

			if (scc_set[i].find(x_not) != scc_set[i].end()) {
				sat = false;
				break;
			}
			std::cout << "SCC: " << i << " " << x << " " << x_not << " ";
		}
		std::cout << "\n";
	}
	std::cout << sat << "\n";

	return 0;
}


















