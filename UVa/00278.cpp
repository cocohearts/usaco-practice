#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    loop(caseN,cases) {
        int m, n;
        char piece;
        cin >> piece >> m >> n;
        if (piece == 'r') {
            cout << min(m,n) << "\n";
        } else if (piece == 'k') {
            cout << (m*n+1)/2 << "\n";
        } else if (piece == 'Q') {
            int answer = min(m,n);
            if (answer < 4) {
                answer = min((max(m,n)+1)/2,answer);
            }
            cout << answer << "\n";
        } else if (piece == 'K') {
            cout << ((m+1)/2) * ((n+1)/2) << "\n";
        }
    }
}