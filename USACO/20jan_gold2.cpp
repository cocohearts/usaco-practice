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

ll DP[5000][5000];
int PF[5000][5000];
int nums[5000];
// int sorted[50];
int indices[2000001];

int main() {
    // freopen("input","r",stdin);
    freopen("threesum.in","r",stdin);
    freopen("threesum.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,Q;
    cin >> N >> Q;
    loop(i,2000001) {
        indices[i] = -1;
    }
    loop(i,N) {
        cin >> nums[i];
        indices[nums[i]+1000000] = i;
    }

    // gen PF
    loop(ind,N) {
        int val = nums[ind];
        int count = 0;
        loop(loc,N) {
            if (nums[loc]==val) {
                ++count;
            }
            PF[ind][loc] = count;
        }
    }

    // failed gen PF
    // loop(ind,N) {
    //     loop(vInd,N) {
    //         if (!ind) {
    //             PF[vInd][ind] = 0;
    //         } else {
    //             PF[vInd][ind] = PF[vInd][ind-1];
    //         }
    //     }
    //     int newInd = lower_bound(sorted,sorted+N,nums[ind])-sorted;
    //     ++PF[newInd][ind];
    // }

    // range DP
    loop(si,N) {
        loop(st,N-si) {
            int en = si+st;
            if (si<=1) {
                DP[st][en] = 0;
                continue;
            }
            int ans = DP[st][en-1] + DP[st+1][en] - DP[st+1][en-1];
            // searching for val in the interval
            int val = -1*(nums[st]+nums[en]);
            if (indices[val+1000000]>=0) {
                int ind = indices[val+1000000];
                ans += PF[ind][en-1]-PF[ind][st];
            }
            DP[st][en] = ans;
        }
    }

    int a,b;
    loop(i,Q) {
        cin >> a >> b;
        --a; --b;
        cout << DP[a][b] << "\n";
    }
}