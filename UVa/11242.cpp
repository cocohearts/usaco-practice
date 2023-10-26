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
    ios::sync_with_stdio(0);
    cin.tie(0);
    int f,r;
    while (true) {
        scanf("%d %d",&f,&r);
        if (!f) break;
        int front[f], rear[r];
        float ratios[f*r];
        int size;
        loop(i,f) {
            scanf("%d",&size);
            front[i] = size;
        }
        loop(i,r) {
            scanf("%d",&size);
            rear[i] = size;
        }
        loop(i,f) {
            loop(j,r) {
                ratios[r*i+j] = ((float)rear[j]) / front[i];
            }
        }
        sort(ratios,ratios+f*r);
        float spread, maxSpread = 0;
        loop(myIndex,f*r-1) {
            spread = ratios[myIndex+1] / ratios[myIndex];
            maxSpread = max(maxSpread,spread);
        }
        printf("%.2f\n",maxSpread);
    }
}