#include <vector>
#include <queue> 

struct node {
	int key, idx;
	node(int key, int idx): key(key), idx(idx) {}
};

bool operator<(const node& x, const node& y) {
	return x.key > y.key;
}

// From Sedgewick, "Algorithms in C++"
std::vector<std::vector<bool>> huffman(std::vector<int>& weights) {
	int N = weights.size();
	std::vector<int> dad(2 * N - 1);
	std::priority_queue<node> pq;

	// Encode.
	int i;
	for (i = 0; i < N; ++i) {
		pq.push(node(weights[i], i));
	}
	while (!pq.empty()) {
		node x = pq.top(); pq.pop();
		node y = pq.top(); pq.pop();
		dad[i] = 0; dad[x.idx] = i; dad[y.idx] = -i;
		weights.push_back(x.key + y.key);
		if (!pq.empty()) { pq.push(node(weights[i], i)); }
		i++;
	}

	// Decode.
	std::vector<std::vector<bool>> code(N);
	int p;
	for (int i = 0; i < N; ++i) {
		p = dad[i];
		while (p != 0) {
			if (p > 0) { code[i].push_back(1); }
			else { code[i].push_back(0); }
			p = dad[abs(p)];
		}
	}

	return code;
}









