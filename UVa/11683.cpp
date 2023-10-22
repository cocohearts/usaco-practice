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

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, len;
    cin >> h >> len;
    while (h) {
        int sums = 0;
        int prevH = h;
        int newH;
        loop(i,len) {
            cin >> newH;
            if (newH < prevH) {
                sums += (prevH - newH);
            }
            prevH = newH;
        }
        cout << sums << "\n";
        cin >> h >> len;
    }
}