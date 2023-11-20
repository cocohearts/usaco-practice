#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef unsigned long long  ull;
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

ull dig_sum(ull X) {
    // including first pos digits, last is dig, under/not yet under X, total number
    ull DP[17][2];
    // digit sum
    ull SM[17][2];
    loop(pos,17) {
        if (!pos) {
            loop(und,2) {
                DP[pos][und] = 0ULL;
                SM[pos][und] = 0ULL;
                if (!und) {
                    DP[pos][und] = 1ULL;
                }
            }
            continue;
        }
        // ull best = (X / ((ull)pow(10L,16-pos)))%10L;
        ull best = X;
        loop(i,16-pos) {
            best /= 10ULL;
        }
        best %= 10ULL;
        loop(und,2) {
            DP[pos][und] = 0ULL;
            SM[pos][und] = 0ULL;
        }
        loop(dig,10) {
            if (dig<best) {
                DP[pos][1] += DP[pos-1][0]+DP[pos-1][1];
                SM[pos][1] += (SM[pos-1][1]+DP[pos-1][1]*dig) + (SM[pos-1][0]+DP[pos-1][0]*dig);
            } else if (dig==best) {
                DP[pos][0] = 1;
                SM[pos][0] += SM[pos-1][0]+dig;
                DP[pos][1] += DP[pos-1][1];
                SM[pos][1] += SM[pos-1][1]+DP[pos-1][1]*dig;
            } else {
                DP[pos][1] += DP[pos-1][1];
                SM[pos][1] += SM[pos-1][1]+DP[pos-1][1]*dig;
            }
        }
    }
    ull ans = SM[16][0]+SM[16][1];
    // if (X==pow(10,15)) {
    //     ans = dig_sum(X-1)+1;
    // }
    return ans;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        ull A,B;
        cin >> A >> B;
        if (A>0L) {--A;}
        cout << dig_sum(B)-dig_sum(A) << "\n";
    }
}