#include <iostream>
#include <vector>
#include <string>
#include <fstream>

template <typename T>
using vec_inv = std::pair<std::vector<T>, long>;

template <typename T>
vec_inv<T> merge_count_split_inv(std::vector<T>& u, std::vector<T>& v) {
	std::vector<T> merged;
	int inv = 0;
	std::size_t n = u.size();
	std::size_t m = v.size();

	// Merge.
	std::size_t i = 0;
	std::size_t j = 0;
	while (i != n && j != m) {
		if (u[i] <= v[j]) {
			merged.push_back(u[i++]);
		} else {
			merged.push_back(v[j++]);
			inv += n - i;
		}
	}

	// Copy elements if one pointer reaches end.
	if (i == n) {
		while (j != m) merged.push_back(v[j++]);
	} else {
		while (i != n) merged.push_back(u[i++]);
	}

	return vec_inv<T>(merged, inv);
}

template <typename T>
vec_inv<T> sort_count_inv(std::vector<T>& A) {
	std::size_t n = A.size();
	if (n < 2) {
		return vec_inv<T>(A, 0);
	} else {
		std::vector<T> lh(A.begin(), A.begin() + n / 2);
		std::vector<T> rh(A.begin() + n / 2, A.end());
		vec_inv<T> left = sort_count_inv(lh);
		vec_inv<T> right = sort_count_inv(rh);
		vec_inv<T> merged = merge_count_split_inv(left.first, right.first);
		return vec_inv<T>(merged.first, left.second + right.second + merged.second); 
	}
}








