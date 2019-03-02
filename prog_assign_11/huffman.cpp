#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "huffman.h"

int main(int argc, char *argv[]) {
	std::string path = argv[1];
	std::ifstream file(path);
	int n, w;
	file >> n;
	std::vector<int> weights;
	weights.reserve(n);
	while (file >> w) { weights.push_back(w); }

	std::vector<std::vector<bool>> code = huffman(weights);

	int max_code = 0;
	int min_code = code.size();
	int len;
	for (int i = 0; i < code.size(); ++i) {
		len = code[i].size(); 
		if (len > max_code) { max_code = len; }
		if (len < min_code) { min_code = len; }
	}
	std::cout << max_code << " " << min_code << "\n";

	return 0;
}