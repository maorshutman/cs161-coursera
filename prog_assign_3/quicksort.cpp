#include <iostream>
#include <vector>
#include <fstream>
#include "quicksort.h"

int main() {
    std::ifstream input("QuickSort.txt");

    std::vector<int> A; 
    int num;
    while(input >> num) { A.push_back(num); }
    std::cout << "Number of elements: " << A.size() << std::endl;

    long counter = 0;
    quicksort<int, std::size_t, long>(A, 0, A.size() - 1, counter);
    for (std::size_t i = 0; i < A.size(); ++i) {
        std::cout << A[i] << std::endl;
    }

    std::cout << "Comparisons: " << counter << std::endl;

    return 0;
}