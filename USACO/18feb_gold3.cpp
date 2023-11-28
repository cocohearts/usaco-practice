#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF INT_MAX
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int main() {
    // freopen("input","r",stdin);
    freopen("taming.in","r",stdin);
    freopen("taming.out","w",stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int sign, signs[N];
    loop(i,N) {
        cin >> sign;
        signs[i]=sign;
    }
    int DP[N][N];
    loop(breakouts,N) {
        iloop(cutoff,breakouts,N) {
            int answer;
            if (!breakouts) {
                if (!cutoff) {
                    answer = (bool)signs[0];
                } else {
                    answer = DP[0][cutoff-1] + (signs[cutoff]!=cutoff);
                }
            } else {
                answer = INF;
                int costs[cutoff+1];
                loop(i,cutoff+1) {
                    costs[i]=cutoff+1-i;
                }
                loop(i,cutoff+1) {
                    if (signs[i]<=i) {
                        --costs[i-signs[i]];
                    }
                }
                iloop(prevCut,breakouts-1,cutoff) {
                    answer = min(answer,DP[breakouts-1][prevCut]+costs[prevCut+1]);
                }
            }
            DP[breakouts][cutoff] = answer;
            cerr << answer << " ";
        }
        cerr << "\n";
    }

    loop(breakouts,N) {
        int answer = INT_MAX;
        iloop(cutoff,breakouts,N) {
            answer = min(answer,DP[breakouts][cutoff]);
        }
        cout << DP[breakouts][N-1] << "\n";
    }
}