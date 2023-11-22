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
int nums[5000];
// int sorted[50];
short int freq[2000001];
const int M = 1000000;

int main() {
    // freopen("input","r",stdin);
    freopen("threesum.in","r",stdin);
    freopen("threesum.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,Q;
    cin >> N >> Q;
    loop(i,2000001) {
        freq[i] = 0;
    }
    loop(i,N) {
        cin >> nums[i];
    }

    // gen #trips with ends
    int comp;
    loop(i,N) {
        iloop(j,i+1,N) {
            if (j>=i+2) {
                comp = -1*(nums[i]+nums[j]);
                if (comp>=-1*M && comp<=M) {
                    DP[i][j] += freq[comp+M];
                }
            }
            ++freq[nums[j]+M];
        }
        iloop(j,i+1,N) {
            --freq[nums[j]+M];
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
                continue;
            }
            DP[st][en] += DP[st][en-1] + DP[st+1][en] - DP[st+1][en-1];
        }
    }

    int a,b;
    loop(i,Q) {
        cin >> a >> b;
        --a; --b;
        cout << DP[a][b] << "\n";
    }
}