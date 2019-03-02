#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "median.h"

std::vector<int> load_data(std::string path) {
	std::vector<int> data;
	std::ifstream file(path);
	int u;
	while (file >> u) { data.push_back(u); }
 	return data;
}

int main(int argc, char *argv[]) {
	std::string path = argv[1];

	std::vector<int> data = load_data(path);
	
	median_queue mq;
	
	int sum = 0;
	for (int i = 0; i < data.size(); ++i) {
		mq.insert(data[i]);
		sum += mq.median();
	}
	std::cout << sum << "\n";

	return 0;
}