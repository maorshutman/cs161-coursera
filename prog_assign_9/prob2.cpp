#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct job {
    int w, l;
    float metric;
    job(int w, int l) : w(w), l(l) {
        metric = float(w) / float(l);
    }
};

bool comp_metric (const job& x, const job& y) {
    return x.metric < y.metric;
}

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    std::ifstream file(path);
    
    int n, w, l;
    file >> n;
    std::vector<job> data;
    
    data.reserve(n);
    while (file >> w >> l) {
        data.push_back(job(w, l));
    }

    std::stable_sort(data.begin(), data.end(), comp_metric);

    long sum = 0;
    long c = 0;
    for (int i = n - 1; i >= 0; i--) {
        c += data[i].l;
        sum += data[i].w * c;
    }
    std::cout << sum << "\n";
    // Answer = 67311454237

    return 0;
}