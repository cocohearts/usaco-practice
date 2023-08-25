#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;



int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    int N;
    cin >> N;
    vector<int> x(N), y(N);
    for (int i=0; i<N; ++i) {cin >> x[i] >> y[i];}

    int distance[N][N];
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            distance[i][j] = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
        }
    }

    int lo = 1;
    int hi = 1250000000;

    while (hi > lo) {
        int X = lo + (hi-lo)/2;

        vector<bool> seen (N);
        vector<int> to_visit;
        seen[0] = true;
        to_visit.push_back(0);
        int current;
        while (to_visit.size() > 0) {
            current = to_visit.back();
            to_visit.pop_back();
            for (int other=0; other<N; ++other) {
                if (distance[current][other] <= X && !seen[other]) {
                    to_visit.push_back(other);
                    seen[other] = true;
                }
            }
        }
        bool success = true;
        for (int i=0; i<N; ++i) {
            if (!seen[i]) {
                success = false;
                break;
            }
        }

        if (success) {
            hi = X;
        } else {
            lo = X+1;
        }
    }
    cout << lo;
}