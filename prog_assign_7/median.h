#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct median_queue {
	int n;
	std::priority_queue<int> h1;
	std::priority_queue <int, std::vector<int>, std::greater<int>> h2;

	median_queue() {
		h1.push(INT_MIN); 
		h2.push(INT_MAX);
	}

	void insert(int x) {
		int u = h1.top();
		int v = h2.top();
		if (x >= u) { h2.push(x); }
		else { h1.push(x); }

		if (h1.size() == h2.size() + 2) {
			h2.push(h1.top());
			h1.pop();
		}
		else if (h1.size() == h2.size() - 2) {
			h1.push(h2.top());
			h2.pop();
		}
	}

	int median() {
		if (h1.size() >= h2.size()) { return h1.top(); }
		else { return h2.top(); }
	}
};
