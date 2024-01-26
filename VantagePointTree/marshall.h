#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <math.h>
using namespace std;
class P {
public:
    double x, y;
    P(double x = 0., double y = 0.) : x(x), y(y) {}
};

double distancia(const P& a, const P& b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int partition(vector<pair<double, P>>& arr, int low, int high) {
    double pivot = arr[high].first;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].first < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<pair<double, P>>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
