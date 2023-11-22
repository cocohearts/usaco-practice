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
const ll L = 500;
ll DP[L][L];
ll binom[L/2+5][L/2];

ll mix(int s1, int s2) {
    // how to mix s1+1 steps and s2 steps? binom
    return binom[s1+s2+1][min(s1+1,s2)];
}

ll myDiv(int dd, int dr) {
    int e = MOD-2;
    ll pow = dr;
    ll ans = dd;
    while (e) {
        if (e%2) {
            ans *= pow;
            ans %= MOD;
        }
        e/=2;
        pow *= pow;
        pow %= MOD;
    }
    return ans;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // binom[m][n] is mCn, m<=250, n<=m/2
    loop(n,L/4+2) {
        ll num = 1;
        binom[n][n] = 1;
        iloop(m,n+1,L/2+5) {
            num *= m;
            num %= MOD;
            num = myDiv(num,m-n);
            num %= MOD;
            binom[m][n] = (ll)num;
        }
    }

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
                DP[si][st]=0;
                continue;
            }
            if (si==1) {
                DP[si][st]=(int)(chars[st]==chars[st+1]);
            }
            ll ans = 0;
            for (int gap=0; gap<si; gap+=2) {
                if (chars[st]==chars[st+gap+1]) {
                    ll poss1, poss2;
                    poss1 = poss2 = 1;
                    if (gap) {
                        poss1 = DP[gap-1][st+1];
                    }
                    if (si-gap-1) {
                        poss2 = DP[si-gap-2][st+gap+2];
                    }
                    ll newV = poss1 * poss2;
                    newV %= MOD;
                    newV *= mix(gap/2,(si-gap-1)/2);
                    ans += newV;
                    ans %= MOD;
                }
            }
            DP[si][st] = ans;
        }
    }
    cout << DP[n-1][0];
}