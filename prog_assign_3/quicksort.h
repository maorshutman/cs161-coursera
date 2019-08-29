#include <iostream>
#include <vector>
#include <fstream>

template <typename T, typename N>
void swap(std::vector<T>& v, N l, N r) {
    T tmp = v[l];
    v[l] = v[r];
    v[r] = tmp;
}

template <typename T, typename N>
N partition(std::vector<T>& v, N l, N r) {
    T p = v[l];
    N i = l + 1;
    for (N j = l + 1; j <= r; ++j) {
        if (v[j] < p) {
            swap(v, j, i);
            i++;
        }
    }
    swap(v, l, i - 1);
    return i - 1;
}

template <typename T, typename N>
N choose_pivot(std::vector<T>& v, N l, N r) {
    N m = (r + l) / 2;
    N first = l; 
    N second = r;
    if (v[l] > v[r]) { first = r; second = l; } 
    if (v[m] >= v[second]) { return second; }
    else if (v[m] < v[second] && v[m] >= v[first]) return m;
    else return first;
}

template <typename T, typename N, typename C>
void quicksort(std::vector<T>& v, N l, N r, C& counter) {
    if (l >= r) return;
    counter += r - l;
    N i = choose_pivot(v, l, r);
    swap(v, l, i);
    N j = partition(v, l, r);
    quicksort(v, l, (j == 0) ? 0 : j - 1, counter);
    quicksort(v, j + 1, r, counter);
}
