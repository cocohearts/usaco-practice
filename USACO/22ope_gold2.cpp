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

// combinatorial model:
// remove 1s, remove everything before 0s
// replace digits with d, pluses with +
// add the stipulation that B's + cannot be preceded by E's +
// similarly, B's d cannot be preceded by E's d
// suffices to represent the problem

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int N;
        cin >> N;
        string B,E;
        char com;
        loop(i,N) {
            cin >> com;
            if (com=='1') continue;
            if (com=='0') {B='d'; continue;}
            if (com=='+') {B+=com; continue;}
            B+='d';
        }
        cin.get();
        loop(i,N) {
            cin >> com;
            if (com=='1') continue;
            if (com=='0') {E='d'; continue;}
            if (com=='+') {E+=com; continue;}
            E+='d';
        }
        int i = B.size(), j=E.size();
        if (!i || !j) {
            cout << 1 << "\n";
            continue;
        }

        int B_DP[i+1][j+1], E_DP[i+1][j+1];
        B_DP[1][0] = E_DP[0][1] = 1;
        B_DP[0][1] = E_DP[1][0] = 0;
        loop(x,i+1) loop(y,j+1) {
            if (x+y<=1) {
                continue;
            }

            int Bans=0, Eans=0;
            if (x) {
                // BB
                Bans += B_DP[x-1][y];
                Bans %= MOD;
                if (y) {
                    // EB, check condition
                    if (B[x-1]!=E[y-1]) {
                        Bans += E_DP[x-1][y];
                        Bans %= MOD;
                    }
                }
            }
            if (y) {
                Eans += E_DP[x][y-1];
                Eans %= MOD;
                if (x) {
                    Eans += B_DP[x][y-1];
                    Eans %= MOD;
                }
            }
            B_DP[x][y]=Bans;
            E_DP[x][y]=Eans;
        }
        cout << (B_DP[i][j] + E_DP[i][j]) % MOD << "\n";
    }
}