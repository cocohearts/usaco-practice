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
int DP[500][500];
int binom[250][250];

int mix(int s1, int s2) {
    // how to mix s1+1 steps and s2 steps? binom

}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    int chars[n];
    loop(i,n) {
        chars[i] = s[i]-'a';
    }
    loop(si,n) {
        loop(st,n-si) {
            if (si%2==0) {
                DP[si][st]==0;
                continue;
            }
            if (si==1) {
                DP[si][st]==(int)(chars[st]==chars[st+1]);
            }
            int ans = 0;
            for (int gap=0; gap<si; gap+=2) {
                if (chars[st]==chars[st+gap+1]) {
                    int poss1, poss2;
                    poss1 = poss2 = 1;
                    if (gap) {
                        poss1 = DP[gap-1][st+gap-1];
                    }
                    if (si-gap-2) {
                        poss1 = DP[si-gap-2][st+gap-1];
                    }
                    ans += poss1 * poss2 * mix(gap/2,(si-gap-1)/2);
                }
            }
        }
    }

}