#include <iostream>
#include <vector>
#include "sort_count_inv.h"

int main() {
    std::ifstream input("IntegerArray.txt");

    std::vector<int> A; 
    int num;
    while(input >> num) { A.push_back(num); }
    std::cout << "Number of ints: " << A.size() << std::endl;

    vec_inv<int> vi = sort_count_inv<int>(A);
    std::cout << "Inversions: " << vi.second << "\n";
    
    return 0;
}