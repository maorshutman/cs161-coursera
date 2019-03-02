#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <functional>

template <typename T>
struct hashtable {
	std::size_t n;
	std::vector<std::list<T>> ht;

	hashtable(int n) : n(n) {
		ht.reserve(n);
		for (int i = 0; i < n; ++i) {
			ht.push_back(std::list<T>());
		}
	}

	std::size_t hash(T key) {
		std::string key_str = std::to_string(key);
		return std::hash<std::string>{}(key_str) % n;
	}

	void insert(T key) {
		std::size_t bucket = hash(key);
		ht[bucket].push_back(key);
	}

	bool search(T key) {
		std::size_t bucket = hash(key);
		for (auto it = ht[bucket].begin(); it != ht[bucket].end(); it++) {
			if (*it == key) { return true; }
		}
		return false;
	}
};

template <typename T>
void print_ht(hashtable<T>& table) {
	for (std::size_t i = 0; i < table.n; ++i) {
		for (auto j = table.ht[i].begin(); j != table.ht[i].end(); j++) {
			std::cout << *j << " ";
		}
		std::cout << "\n";
	}
}
