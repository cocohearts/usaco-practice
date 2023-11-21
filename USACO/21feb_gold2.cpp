#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define MOD 1000000007
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int DP[300][300];

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int nums[N];
    loop(i,N) {
        cin >> nums[i];
    }
    loop(si,N) {
        loop(st,N-si) {
            if (st==2 && si == 4) {
                int k = 4;
            }
            int en = st+si;
            if (!si) {
                DP[st][en] = 1;
                continue;
            }
            if (nums[st]==nums[st+1]) {
                DP[st][en] = DP[st+1][en];
                continue;
            }
            if (nums[en-1]==nums[en]) {
                DP[st][en] = DP[st][en-1];
                continue;
            }
            int best = INT_MAX;
            iloop(mid,st,en) {
                int cur = DP[st][mid] + DP[mid+1][en];
                if (nums[mid+1]==nums[st]) {
                    cur = DP[st+1][mid] + DP[mid+1][en];
                }
                if (nums[mid]==nums[mid+1]) {
                    --cur;
                }
                best = min(best,cur);
            }
            DP[st][en] = best;
        }
    }
    cout << DP[0][N-1];
}