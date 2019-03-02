#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int
knapsack(std::vector<std::vector<int>>& elems, int n, int W) {
	std::vector<std::vector<int>> A(n + 1);
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= W; ++j) { A[i].push_back(0); }
	}
	int v, w, sp_1, sp_2;
	for (int i = 1; i <= n; ++i) {
		for (int x = 0; x <= W; ++x) {
			w = elems[i - 1][1]; v = elems[i - 1][0];
			sp_1 = A[i - 1][x]; sp_2 = 0;
			if (w <= x) { sp_2 = A[i - 1][x - w] + v; }
			A[i][x] = sp_1 >= sp_2 ? sp_1 : sp_2;
		}
	}
	return A[n][W];
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];
	std::ifstream file(path);
	int W, n;
	file >> W >> n;
	std::vector<std::vector<int>> elems(n);
	int v, w;
	int i = 0;
	while (file >> v >> w) { 
		elems[i].push_back(v);
		elems[i].push_back(w);
		i++;
	}

	for (int i = 0; i < elems.size(); ++i) {
		std::cout << elems[i][0] << " " << elems[i][1] << "\n";
	}

	int opt = knapsack(elems, n, W);
	std::cout << opt << "\n";

	return 0;
}





