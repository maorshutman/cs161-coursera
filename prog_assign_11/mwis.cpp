#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>


std::set<int> mwis(std::vector<int>& weights) {
	int N = weights.size();
	std::vector<int> A(N + 1);
	
	A[0] = 0; A[1] = weights[0];
	for (int i = 2; i <= N; ++i) {
		A[i] = (A[i - 1] > A[i - 2] + weights[i - 1]) ? A[i - 1] : A[i - 2] + weights[i - 1]; 
	}

	std::set<int> mwis_set;
	int i = N;
	while(i >= 1) {
		if (A[i - 1] >= A[i - 2] + weights[i - 1]) {
			i--;
		} else {
			mwis_set.insert(i - 1);
			i -= 2;
		}
	}

	return mwis_set;
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];
	std::ifstream file(path);
	int n, w;
	file >> n;
	std::vector<int> weights;
	weights.reserve(n);
	while (file >> w) { weights.push_back(w); }

	std::set<int> mwis_set = mwis(weights);

	int a[8] = {1, 2, 3, 4, 17, 117, 517, 997};
	for (int i = 0; i < 8; ++i) {
		std::cout << mwis_set.count(a[i] - 1);
	}
	std::cout << "\n";

	return 0;
}





