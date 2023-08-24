#include <iostream>

using namespace std;

int main() {
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);

    long long N, K, M;
    cin >> N >> K >> M;

    long long lo = 1LL;
    long long hi = K;
    while (lo < hi) {
        long long X = (lo + hi + 1)/2;
        long long G = 0;
        long long time = 0;
        long long Y, extra_time;
        while (time < K && G < N) {
            Y = (N-G)/X;
            if (Y < M) {
                G += (K - time) * M;
                break;
            }
            extra_time = (N - G - Y * X)/Y + 1;
            time += extra_time;
            if (time > K) {
                G += (K - time + extra_time) * Y;
                break;
            }
            G += Y * extra_time;
        }
        if (G >= N) {
            lo = X;
        } else {
            hi = X-1;
    }
        }
    cout << lo << endl;
}