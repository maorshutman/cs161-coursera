#include <vector>
#include <set>
#include <random>

struct vert_list {
	std::vector<int> vert;
	vert_list () {};
	~vert_list () {};
};

struct Adjlist {
	std::vector<vert_list> adj;
	std::set<int> active_vert;
	
	Adjlist (int n) {
		for (int i = 0; i < n; ++i) { active_vert.insert(i); }
	}

	Adjlist& operator=(const Adjlist& x) {
		adj = x.adj;
		active_vert = x.active_vert;
		return *this;
	}

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

	void print_vert() {
		std::cout << "Active vertices: ";
		for(auto it = active_vert.begin(); it != active_vert.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
	}

	void add_node(int x, int v) { adj[v].vert.push_back(x); }

	void add_vert() { adj.push_back(vert_list()); }

	void contract(int u, int v) {
		this->add_vert();
		int last = adj.size() - 1;

		// Create the list of vertices for the new vertex.
		for (int i = 0; i < adj[u].vert.size(); ++i) {
			int x = adj[u].vert[i];
			if (x != u && x != v) { adj[last].vert.push_back(x); }
		}
		for (int i = 0; i < adj[v].vert.size(); ++i) {
			int x = adj[v].vert[i];
			if (x != u && x != v) { adj[last].vert.push_back(x); }
		}

		// Replace u and v by last.
		// This is O(n^2) ...
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

		adj[u] = vert_list();
		adj[v] = vert_list();
		active_vert.insert(last);
		active_vert.erase(u);
		active_vert.erase(v);
	}

	int rand_vert() {
		std::set<int>::const_iterator it(active_vert.begin());
		std::advance(it, std::rand() % active_vert.size());
		return *it;
	}
};

int contract_adjlist(Adjlist& adjlist) {
	while (adjlist.active_vert.size() > 2) {
		int u, v;
		u = adjlist.rand_vert();
		int r = std::rand() % adjlist.adj[u].vert.size();
		v = adjlist.adj[u].vert[r];
		adjlist.contract(u, v);
	}
	int u = adjlist.adj.size() - 1;
	return adjlist.adj[u].vert.size();
}

int karger(Adjlist adjlist, int trials) {
	int min_cut = adjlist.adj.size();
	int cut;
	for (int i = 0; i < trials; ++i) {
		std::cout << i << "\n";
		Adjlist al = adjlist;
		cut = contract_adjlist(al);
		if (cut < min_cut) { min_cut = cut; }
	}
	return min_cut;
}
