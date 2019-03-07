#include <vector>
#include <stack> 

struct graph {
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;

	graph(int n) {
		for (int i = 0; i < n; ++i) { 
			adj.push_back(std::vector<int>());
			visited.push_back(0);
		}
	}

	graph& operator=(const graph& g) {
		adj = g.adj;
		visited = g.visited;
		return *this;
	}

	void add_edge(int u, int v) { adj[u].push_back(v); };
};

void dfs_1st(graph* g, int u, int& t, std::vector<int>& f) {
	g->visited[u] = 1;
	for (int v = 0; v < g->adj[u].size(); ++v) {
		if (!g->visited[g->adj[u][v]]) {
			dfs_1st(g, g->adj[u][v], t, f);
		}
	}
	f[t] = u;
	t++;
}

void dfs_2nd(graph* g, int u, int& s, std::vector<int>& leader) {
	std::stack<int> st;
	st.push(u);

	int v;
	while (!st.empty()) {
		v = st.top();
		st.pop();
		if (!g->visited[v]) {
			g->visited[v] = 1;
			leader[v] = s;
			for (int w = 0; w < g->adj[v].size(); ++w) {
				st.push(g->adj[v][w]);
			}
		}
	}
}

void dfs_1st_loop(graph* g, int n, std::vector<int>& f) {
	int t = 0;
	for (int i = 0; i < g->adj.size(); ++i) {
		if (!g->visited[i]) { dfs_1st(g, i, t, f); }
	}
}

void dfs_2nd_loop(graph* g, int n,
				  std::vector<int>& f,
				  std::vector<int>& leader) {
	int s, w;
	for (int i = n - 1; i >= 0; --i) {
		w = f[i];
		if (!g->visited[w]) {
			s = w;
			dfs_2nd(g, w, s, leader);
		}
	}
}

void print_graph(graph* g) {
	int u;
	for (int i = 0; i < g->adj.size(); ++i) {

		if (i % 2 == 0) { std::cout << i / 2 + 1 << " -> "; } 
		else { std::cout << "!" << i / 2 + 1 << " -> "; }

		for (int j = 0; j < g->adj[i].size(); ++j) {
			u = g->adj[i][j];
			if (u % 2 == 0) { std::cout << u / 2 + 1 << " -> "; } 
			else { std::cout << "!" << u / 2 + 1 << " -> "; }
		}

		std::cout << "\n";
	}
}












