#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map> 
#include "hashtable.h"

template <typename T>
std::vector<T> load_data(std::string path) {
	std::vector<T> data;
	std::ifstream file(path);
	T u;
	while (file >> u) { 
		data.push_back(u); 
	}
 	return data;
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];

	std::vector<long> data = load_data<long>(path);

	std::size_t n = data.size();
	hashtable<long> ht(10 * n);
	for (int i = 0; i < n; ++i) { ht.insert(data[i]); }

	// The std hashtable is faster.
	std::unordered_map<long, long> map;
	for (int i = 0; i < n; ++i) { map[data[i]] = data[i]; }

	long target, y;
	int counter = 0;
	for (long t = -10000; t <= 10000; ++t) {
		std::cout << t << " " << counter << "\n";
		for (std::size_t j = 0; j < n; ++j) {
			//if (ht.search(t - data[j])) { counter++; }
			y = t - data[j]; /* x = data[j] */
			if ((y != data[j]) && map.count(y)) {
				counter++;
				break; 
			}
		}
	}
	std::cout << counter << "\n";

	return 0;
}
