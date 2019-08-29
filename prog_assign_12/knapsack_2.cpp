#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// A bit of a hack ?
std::string key(int x, int y) {
    return std::to_string(x) + '_' + std::to_string(y);
}

int
knapsack(std::vector<std::vector<int>>& elems,
         std::unordered_map<std::string, int>& um,
         int i, int x)
{
    if (i == 0) { return 0; }

    int opt;
    int sp_1 = 0, sp_2 = 0;
    int v = elems[i - 1][0];
    int w = elems[i - 1][1];
    std::string k = key(i, x);

    if (um.find(k) != um.end()) {
        return um[k];
    } else {
        sp_1 = knapsack(elems, um, i - 1, x);
        sp_2 = (x >= w) ? knapsack(elems, um, i - 1, x - w) + v : 0;
    }

    opt = sp_1 >= sp_2 ? sp_1 : sp_2;
    um[k] = opt;
    return opt;
}

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    std::ifstream file(path);
    int W, n;
    file >> W >> n;
    std::vector<std::vector<int>> elems(n);
    int v, w;
    int i = 0;
    while (file >> v >> w) { 
        elems[i].push_back(v);
        elems[i].push_back(w);
        i++;
    }

    for (int i = 0; i < elems.size(); ++i) {
        std::cout << elems[i][0] << " " << elems[i][1] << "\n";
    }

    std::unordered_map<std::string, int> um;
    int opt = knapsack(elems, um, n, W);
    std::cout << opt << "\n";

    return 0;
}





