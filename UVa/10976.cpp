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
    int k,x,y;
    while (cin >> k) {
        vii pairs;
        for (y=k+1;y<=2*k;++y) {
            if (k*y % (y-k) == 0) {
                x = k*y/(y-k);
                pairs.PB(MP(x,y));
            }
        }
        printf("%u\n",(int)pairs.size());
        sloop(xyPair,pairs) {
            printf("1/%u = 1/%u + 1/%u\n",k,xyPair.F,xyPair.S);
        }
    }
}