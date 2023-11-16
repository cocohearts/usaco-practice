#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 2000000000
#define MOD 1000000007
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

ii DP[1<<20];

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,W;
    cin >> N >> W;
    int weights[N];
    loop(i,N) {
        cin >> weights[i];
    }
    loop(bm,1<<N) {
        if (!bm) {
            DP[bm] = MP(1,0);
            continue;
        }
        ii ans = MP(INT_MAX,0);
        loop(ind,N) {
            if (bm&1<<ind) {
                int last = DP[bm^1<<ind].S+weights[ind];
                int rides = DP[bm^1<<ind].F;
                if (last>W) {
                    last = weights[ind];
                    ++rides;
                }
                if (rides < ans.F) {
                    ans.F=rides; ans.S=last;
                } else if (rides==ans.F) {
                    ans.S = min(ans.S,last);
                }
            }
        }
        DP[bm] = ans;
    }
    cout << DP[(1<<N)-1].F;
}