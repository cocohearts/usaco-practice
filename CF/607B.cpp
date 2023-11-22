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

// DP[si][st]
const int L = 500;
int DP[L][L];

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int nums[n];
    loop(i,n) {
        cin >> nums[i];
    }
    loop(si,n) {
        loop(st,n-si) {
            if (!si) {
                DP[si][st] = 1;
                continue;
            }
            if (si==1) {
                DP[si][st] = 1+(nums[st]!=nums[st+1]);
            }
            int en = st+si;
            int ans = INT_MAX;
            // match
            iloop(ma,st,en+1) {
                if (nums[st]==nums[ma]) {
                    int cur;
                    if (ma<=st+1) {
                        int diff = ma-st+1;
                        cur = 1+DP[si-diff][st+diff];
                        if (ma==en) {
                            cur = 1;
                        }
                    } else {
                        cur = DP[ma-st-2][st+1];
                        if (ma<en) {
                            cur += DP[en-ma-1][ma+1];
                        }
                    }
                    ans = min(ans,cur);
                }
            }
            DP[si][st] = ans;
        }
    }
    cout << DP[n-1][0];
}