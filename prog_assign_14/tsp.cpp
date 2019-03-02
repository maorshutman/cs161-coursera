#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <math.h>

#define INF 1.0e8

int swar(uint i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

struct vert_set {
	uint set;
	vert_set (uint i) { set = i; }

	uint
	wo_vert(int j) { return set ^ (1 << j); }

	void
	rm_vert(int j) { set = wo_vert(j); }

	bool 
	has_vert(int j) { return (set >> j) & 1; }
};

int to_idx(vert_set s) {
	return s.set >> 1;
}

float
min_over_set (std::vector<std::vector<float>>& d,
	 std::vector<std::vector<float>>& A,
	 vert_set set,
	 int j) {

	int n = d.size();
	vert_set s(set.wo_vert(j));

	float dist, min_dist = INF;
	int S;
	for (int k = 0; k < n; ++k) {
		if (s.has_vert(k)) {			
			S = to_idx(s);
			dist = A[S][k] + d[k][j];
			if (dist < min_dist) { min_dist = dist; }
		} 
	}
	return min_dist;
}

float 
tsp(std::vector<std::vector<float>>& d,
	std::vector<std::vector<vert_set>>& sp_list,
	std::vector<std::vector<float>>& A) {

	int n = d.size();

	int S;
	for (int m = 0; m < sp_list.size(); ++m) {
		for (auto set : sp_list[m]) {
			for (int j = 1; j < n; ++j) {
				if (set.has_vert(j)) {
					S = to_idx(set);
					A[S][j] = min_over_set(d, A, set, j);
				}
			}
		}
		std::cout << "m = " << m + 2 << "\n";
	}

	// Brute force final search.
	float dist, opt = INF;
	int last = A.size() - 1;
	for (int j = 1; j < A[0].size(); ++j) {
		dist = A[last][j] + d[j][0];
		if (dist < opt) { opt = dist; }
	}

	return opt;
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];
	
	// Read poits.
	std::ifstream file(path);
	int n;
	file >> n;
	std::vector<std::vector<float>> pts(n);
	float x, y; 
	int i = 0;
	while (file >> x >> y) {
		pts[i].push_back(x); pts[i].push_back(y);
		i++;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << pts[i][0] << " " << pts[i][1] << "\n";
	}

	// Calc. distances for all pairs once for later. n^2 space.
	std::vector<std::vector<float>> d(n);
	float dist;
	for (int i = 0; i < n; ++i) { 
		for (int j = 0; j < n; ++j) {
			dist = sqrt((pts[i][0] - pts[j][0]) * (pts[i][0] - pts[j][0]) +
			 			(pts[i][1] - pts[j][1]) * (pts[i][1] - pts[j][1]));
			d[i].push_back(dist);
		}
	}

	// The A array. n * 2^(n - 1) space.
	std::vector<std::vector<float>> A(pow(2, n - 1));
	for (int i = 0; i < A.size(); ++i) {
		A[i].reserve(n);
		for (int j = 0; j < n; ++j) { A[i].push_back(0); }
	}
	// Fill base case.
	A[0][0] = 0.0;
	for (int i = 1; i < A.size(); ++i) { A[i][0] = INF; }

	// Debug.
	// std::cout << A[0].size() << "\n";
	// for (int i = 0; i < A.size(); ++i) {
	// 	for (int j = 0; j < n - 1; ++j) {
	// 		std::cout << A[i][j] << " ";
	// 	}
	// 	std::cout << "\n";
	// }

	// Build all subproblems.
	std::vector<std::vector<vert_set>> sp_list(n - 1);
	uint max = pow(2, n - 1);
	for (uint i = 1; i < max; ++i) {
		sp_list[swar(i) - 1].push_back(vert_set((i << 1) + 1));
	}

	// Debug.
	// for (int i = 0; i < sp_list.size(); ++i) {
	// 	std::cout << i + 2 << "->";
	// 	for (int j = 0; j < sp_list[i].size(); ++j) {
	// 		std::cout << sp_list[i][j].set << " ";
	// 	}
	// 	std::cout << "\n";
	// }

	float opt = tsp(d, sp_list, A);
	std::cout << "Opt path length: " << opt << "\n";
	
	return 0;
}












