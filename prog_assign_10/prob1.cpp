#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct edge {
	int u, v, dist;
	edge(int u, int v, int dist) : u(u), v(v), dist(dist) {}
};

bool operator<(const edge& x, const edge& y) {
	return x.dist < y.dist;
}

struct union_find {
	std::vector<int> component;
	std::vector<std::vector<int>> cc_elem;

	union_find(int n) {
		component.reserve(n);
		cc_elem.reserve(n);
		for (int i = 0; i < n; ++i) {
			component.push_back(i);
			std::vector<int> v = {i};
			cc_elem.push_back(v);
		}
	}

	int find(int x) {
		return component[x];
	}

	int size(int x) {
		return cc_elem[x].size();
	}

	void unify(int x, int y) {
		int size_x = size(x);
		int u;
		for (int i = 0; i < size_x; ++i) {
			u = cc_elem[x].back();
			component[u] = y;
			cc_elem[y].push_back(u);
			cc_elem[x].pop_back();
		}
	}

	bool union_comp(int x, int y) {
		int c1 = find(x);
		int c2 = find(y);
		if (c1 != c2) {
			if (size(c1) >= size(c2)) { unify(c2, c1); }
			else { unify(c1, c2); }
			return true;
		}
		return false;
	}
};

void print_cc(union_find& uf) {
	for (int i = 0; i < uf.component.size(); ++i) {
		std::cout << i + 1 << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < uf.component.size(); ++i) {
		std::cout << uf.component[i] + 1 << " ";
	}
	std::cout << "\n";
}

int cluster(std::vector<edge>& edges,
						 union_find& uf,
						 int n, int k) {
	int cc_counter = n;
	
	int u, v;
	int i = 0;
	while (cc_counter > k) {
		u = edges[i].u;
		v = edges[i].v;
		if (uf.union_comp(u, v)) { cc_counter--; }
		i++;
	}

	while (1) {
		u = edges[i].u;
		v = edges[i].v;
		if (uf.find(u) != uf.find(v)) { break; }
		i++;
	}

	return i;
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];
	std::ifstream file(path);
	int n;
	file >> n;

	std::vector<edge> edges;
	int u, v, dist;
	while (file >> u >> v >> dist) {
		edges.push_back(edge(u - 1, v - 1, dist));
	}

	std::sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size(); ++i) {
		std::cout << edges[i].u + 1 << " " << edges[i].v + 1 << " " << edges[i].dist << "\n";
	}

	union_find uf(n);
	int last_edge = cluster(edges, uf, n, 4);
	std::cout << edges[last_edge].dist << "\n";

	return 0;
}
