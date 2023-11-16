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

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string song;
    cin >> song;

    vi occurred(26,0);
    vector<vi> initAdj(26,vi(26,0));
    loop(ind,song.size()) {
        ++occurred[song[ind]-'a'];
        if (ind != song.size()-1) {
            ++initAdj[song[ind]-'a'][song[ind+1]-'a'];
        }
    }
    vi realInds(26,0);
    int realInd=0;
    loop(i,26) {
        if (occurred[i]) {
            realInds[i] = realInd;
            ++realInd;
        }
    }
    int adj[20][20];
    loop(i,26) loop(j,26) {
        if (occurred[i] && occurred[j]) {
            adj[realInds[i]][realInds[j]] = initAdj[i][j];
        }
    }
    int N = realInd;
    loop(bm,1<<N) {
        if (!bm) {
            DP[bm]=0;
            continue;
        }
        int ans = INT_MAX;
        loop(ind,N) {
            if (bm & 1<<ind) {
                int costs = DP[bm^1<<ind];
                loop(jnd,N) {
                    if (bm & 1<<jnd) {
                        costs += adj[ind][jnd];
                    }
                }
                ans = min(ans,costs);
            }
        }
        DP[bm] = ans;
    }
    cout << DP[(1<<N)-1]+1;
}