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

int DP[1<<20];
int showtimes[20][1000];
int durations[20];
int showings[20];

int main() {
    // freopen("input","r",stdin);
    freopen("movie.in","r",stdin);
    freopen("movie.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,L;
    cin >> N >> L;
    loop(i,N) {
        cin >> durations[i];
        cin >> showings[i];
        loop(j,showings[i]) cin >> showtimes[i][j];
    }

    int ans = INT_MAX;
    
    loop(bM,1<<N) {
        if (!bM) {DP[0]=0; continue;}
        int best = 0;
        loop(ind,N) {
            if (bM & 1<<ind) {
                int prev=DP[bM^1<<ind];
                int mid, bot = 0, top = showings[ind]-1;
                while (top!=bot) {
                    mid = (bot+top+1)/2;
                    if (showtimes[ind][mid]>prev) {
                        top = mid-1;
                    } else {
                        bot = mid;
                    }
                }
                if (showtimes[ind][bot] <= prev) {
                    prev = max(prev,showtimes[ind][bot] + durations[ind]);
                }
                best = max(best,prev);
            }
        }
        DP[bM] = best;
        if (best>=L) {
            ans = min(ans,__builtin_popcount(bM));
        }
    }
    if (ans==INT_MAX) {
        cout << -1;
    } else cout << ans;
}