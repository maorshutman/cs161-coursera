#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "mincut.h"

int main() {
	// Set random seed.
	std::srand(unsigned(std::time(0)));

	// Read data from file.
	std::string line;
  std::vector<std::vector<int>> adjlist_data;
  while (getline(std::cin, line)) {
  	std::istringstream is(line);
  	adjlist_data.push_back(std::vector<int>(
  		std::istream_iterator<int>(is), 
  		std::istream_iterator<int>())
  	);
	}

	// Build adjacency list.
	int n = adjlist_data.size();
	Adjlist adjlist(n);
	for (int i = 0; i < adjlist_data.size(); ++i) {
		adjlist.add_vert();	
		for (int j = 1; j < adjlist_data[i].size(); ++j) {
			adjlist.add_node(adjlist_data[i][j] - 1, i);
		}
	}
	adjlist.print();

	// Calc. min cut.
	std::cout << karger(adjlist, 4000) << "\n";

	return 0;
}











