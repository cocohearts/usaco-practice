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

int DP[5000][5000];
bool PL[5000][5000];

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int N = s.size();
    loop(si,N) {
        loop(st,N-si) {
            int end = st+si;
            if (!si) {
                DP[st][end] = 1;
                PL[st][end] = true;
                continue;
            }
            PL[st][end] = false;
            DP[st][end] = DP[st+1][end] + DP[st][end-1];
            if (si>=2) {
                DP[st][end] -= DP[st+1][end-1];
            }
            if (s[st]==s[end]) {
                if (PL[st+1][end-1] || si==1) {
                    ++DP[st][end];
                    PL[st][end] = true;
                }
            }
        }
    }
    int q;
    cin >> q;
    int a,b;
    loop(qNum,q) {
        cin >> a >> b;
        --a; --b;
        cout << DP[a][b] << "\n";
    }
}