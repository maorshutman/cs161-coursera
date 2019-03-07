#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <math.h>
#include <unordered_set>
#include <iomanip>

#define INF 1.0e20

double eucl_sq(double x1, double y1, double x2, double y2) {
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

double eucl(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int nn(int v, 
	std::vector<std::vector<double>>& pts,
	std::unordered_set<int>& vertices) {

	double d, min_dist = INF;
	int nn_idx = INT_MAX;
	for (int i = 0; i < pts.size(); ++i) {
		if (vertices.find(i) != vertices.end()) { continue; }

		d = eucl_sq(pts[v][0], pts[v][1], pts[i][0], pts[i][1]);

		if (d < min_dist) {
			min_dist = d;
			nn_idx = i;
		} else if (d == min_dist) {
			if (i < nn_idx) { nn_idx = i; }
		}
	}

	return nn_idx;
}

double approx_tsp(std::vector<std::vector<double>>& pts) {
	int n = pts.size();
	std::vector<int> path;
	path.reserve(n + 1);
	std::unordered_set<int> vertices;

	int v = 0;
	vertices.insert(v);
	path.push_back(v);

	while (path.size() != n) {
		v = nn(v, pts, vertices);
		vertices.insert(v);
		path.push_back(v);
	}
	path.push_back(0);

	double path_length = 0.0;
	int u, w;
	for (int i = 0; i < path.size() - 1; ++i) {
		u = path[i]; w = path[i + 1];
		path_length += eucl(pts[u][0], pts[u][1], pts[w][0], pts[w][1]);
	}

	return path_length;
}

int main(int argc, char *argv[]) {
	std::string filepath = argv[1];
	
	std::ifstream file(filepath);
	int n;
	file >> n;
	std::vector<std::vector<double>> pts(n);
	double x, y; 
	int idx, i = 0;
	while (file >> idx >> x >> y) {
		pts[i].push_back(x); pts[i].push_back(y);
		i++;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << pts[i][0] << " " << pts[i][1] << "\n";
	}

	double path_length = approx_tsp(pts);
	std::cout << std::setprecision(15) << path_length << std::endl;

	return 0;
}
