#include <vector>

struct vert_list {
	std::vector<int> vert;
	std::vector<int> contr;
	vert_list () {};
	~vert_list () {};
};

struct Adjlist {
	std::vector<vert_list> adj;

	// Adjlist (int n) { 
	// 	for (int i = 0; i < n; ++i) {
	// 		contr.push_back(std::vector<int>());
	// 	}
	// }

	void print () {
		for (int i = 0; i < adj.size(); ++i) {
	 		std::cout << i << " -> ";
	 		for (int j = 0; j < adj[i].vert.size(); ++j) {
	 			std::cout << adj[i].vert[j] << " ";
	 		}
	 		std::cout << "\n";
	 	}		
	 	std::cout << "o~o~o~o~o~o~o~o~o~o~o~o~o" << "\n";
	}

	void print_contracted () {
		for (int i = 0; i < adj.size(); ++i) {
	 		std::cout << i << " -> ";
	 		for (int j = 0; j < adj[i].contr.size(); ++j) {
	 			std::cout << adj[i].contr[j] << " ";
	 		}
	 		std::cout << "\n";
	 	}		
	 	std::cout << "o~o~o~o~o~o~o~o~o~o~o~o~o" << "\n";
	}

	void add_node(int x, int v) { adj[v].vert.push_back(x); }

	void add_vert() { adj.push_back(vert_list()); }

	void contract(int u, int v) {
		this->add_vert();
		int last = adj.size() - 1;

		// Add vertices to contracted list.
		// for (int i = 0; i < adj[u].contr.size(); ++i) {
		// 	adj[last].contr.push_back(adj[u].contr[i]); 
		// }
		// for (int i = 0; i < adj[v].contr.size(); ++i) {
		// 	adj[last].contr.push_back(adj[v].contr[i]);
		// }
		// adj[last].contr.push_back(u);
		// adj[last].contr.push_back(v);

		// Create the list of vertices for the new vertex.
		for (int i = 0; i < adj[u].vert.size(); ++i) {
			int x = adj[u].vert[i];
			if (x != u && x != v) {adj[last].vert.push_back(x); }
		}
		for (int i = 0; i < adj[v].vert.size(); ++i) {
			int x = adj[v].vert[i];
			if (x != u && x != v) {adj[last].vert.push_back(x); }
		}

		// Replace u and v by last.
		// TODO this is O(n^2)
		for (int i = 0; i < adj[u].vert.size(); ++i) {
			int x = adj[u].vert[i];
			for (int j = 0; j < adj[x].vert.size(); ++j) {
				if (adj[x].vert[j] == u) { adj[x].vert[j] = last; }
			}
		}
		for (int i = 0; i < adj[v].vert.size(); ++i) {
			int x = adj[v].vert[i];
			for (int j = 0; j < adj[x].vert.size(); ++j) {
				if (adj[x].vert[j] == v) { adj[x].vert[j] = last; }
			}
		}

    // TODO
		adj[u] = vert_list();
		adj[v] = vert_list();
	}
};







