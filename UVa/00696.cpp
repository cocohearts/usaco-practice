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

    int m,n;
    while (true) {
        cin >> m >> n;
        if (!(m+n)) break;
        int answer = (m*n+1)/2;
        if (min(m,n)==1) {
            answer = max(m,n);
        } else if (min(m,n)==2) {
            answer = 2*(2*((max(m,n))/4) + min(max(m,n)%4,2));
        }
        cout << answer << " knights may be placed on a " << m << " row " << n << " column board.\n";
    }
}