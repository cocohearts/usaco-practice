#include <iostream>
#include <queue>
#include <string>


using ll = long long;
using namespace std;

ll P = 1e9+7;

ll exp(ll n, ll e) {
    ll answer = 1;
    ll pow = (ll) n;
    while (e > 0) {
        if (e % 2) {
            answer *= pow;
            answer %= P;
        }
        pow *= pow;
        pow %= P;
        e /= 2;
    }
    return answer;
}

ll mul(priority_queue<ll> p) {
    ll count = 0;
    ll answer = 1;
    ll number = p.top();
    p.pop();
    p.push(0);
    while (p.size()) {
        ++count;
        int max = p.top();
        p.pop();
        while (number > max) {
            answer *= exp(number, count);
            answer %= P;
            --number;
        }
    }
    return answer;
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    freopen("route.in", "r", stdin);
    ll N;
    cin >> N;
    // cout << N;
    // cout << "received" << endl;
    priority_queue<ll> maxes;
    priority_queue<ll> mins;
    ll last = -1;
    ll current = -1;
    for (ll i=0; i<N; ++i) {
        if (i > 0) {
            last = current;
        }
        // cout << "waiting" << endl;
        cin >> current;
        // cout << "received" << endl;
        // cout << current;
        current /= 2;
        if (i > 0) {
            if (current > last) {
                maxes.push(max(last, current)-1);
                mins.push(abs(last-current));
                mins.push(min(last, current)-1);
            } else if (last > current) {
                maxes.push(max(last, current));
                mins.push(abs(last-current));
                mins.push(min(last, current));
            }
        }
        // cout << "next cycle" << endl;
    }
    // cout << "out cycle" << endl;
    ll num = mul(maxes);
    ll denom = mul(mins);
    // cout << num << denom << endl;
    ll answer = num * exp(denom, P-2) % P;
    cout << answer;
}