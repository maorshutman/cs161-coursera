#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map> 

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

std::vector<uint> get_masks(int n_bits) {
	std::vector<uint> masks;
	// 0 bit mask.
	masks.push_back(0);
	// 1 bit masks.
	for (int i = 0; i < n_bits; ++i) {
		masks.push_back(1 << i);
	}
	// 2 bit masks.
	for (int i = 0; i < n_bits - 1; ++i) {
		for (int j = i + 1; j < n_bits; ++j) {
			masks.push_back((1 << j) + (1 << i));
		}
	}
	return masks;
}

int cluster(std::vector<uint>& data,
						std::vector<uint>& masks,
						std::unordered_map<uint, int> umap,
						union_find& uf,
						int n)
{
	uint key;
	int v;
	int cc_counter = n;
	for (int i = 0; i < masks.size(); ++i) {
		for (int u = 0; u < data.size(); ++u) {
			key = data[u] ^ masks[i];
			v = umap[key];
			if (v != 0) {
				if (uf.union_comp(u, v - 1)) {
					cc_counter--;
				}
			}
		}
	}
	return cc_counter;
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];

	std::ifstream file(path);
	std::string line;
	int n, n_bits;
	std::getline(file, line);
	std::istringstream is(line);
  is >> n >> n_bits;

  std::vector<uint> data;
	data.reserve(n);

	while (std::getline(file, line)) {
    line.erase(std::remove(line.begin(), line.end(), ' '),
    					 line.end());
    data.push_back(std::stoi(line, nullptr, 2));
	}
	for (int i = 0; i < data.size(); ++i) {
		std::cout << i << " " << data[i] << "\n";
	}

	std::vector<uint> masks = get_masks(n_bits);

	std::unordered_map<uint, int> umap;
	for (int i = 0; i < n; ++i) {
		umap[data[i]] = i + 1;
	}

	union_find uf(n);
	
	int k = cluster(data, masks, umap, uf, n);
	std::cout << k << "\n";

	return 0;
}












