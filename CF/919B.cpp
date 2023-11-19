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

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    int top = 1e9;
    int bot = 0;
    while (top>bot) {
        int mid = (top+bot)/2;

        // DP[posits_filling][dig_sum][under_alr]
        int DP[10][11][2];
        double pow_arr [] = {1e8, 1e7, 1e6, 1e5, 1e4, 1e3, 1e2, 1e1, 1};
        loop(pos,10) {
            if (!pos) {
                loop(sum,11) {
                    if (sum) {
                        loop(under,2) {
                            DP[pos][sum][under] = 0;
                        }
                    } else {
                        DP[pos][sum][0] = 1;
                        DP[pos][sum][1] = 0;
                    }
                }
                continue;
            }
            loop(sum,11) {
                loop(under,2) {
                    DP[pos][sum][under] = 0;
                }
            }
            int best = (mid/(int)pow_arr[pos-1])%10;
            loop(dig,10) {
                iloop(sum,dig,11) {
                    if (dig<best) {
                        DP[pos][sum][1] += DP[pos-1][sum-dig][0]+DP[pos-1][sum-dig][1];
                    } else if (dig==best) {
                        DP[pos][sum][0] += DP[pos-1][sum-dig][0];
                        DP[pos][sum][1] += DP[pos-1][sum-dig][1];
                    } else {
                        DP[pos][sum][1] += DP[pos-1][sum-dig][1];
                    }
                    DP[pos][sum][0] %= MOD;
                    DP[pos][sum][1] %= MOD;
                }
            }
        }

        int ans = DP[9][10][0]+DP[9][10][1];
        if (ans>=k) {
            top = mid;
        } else {
            bot = mid+1;
        }
    }
    cout << bot;
}