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

// num_paid (inc. current), left_to_pay; num=-1 if impossible
ii DP[1<<20];

int main() {
    // ii DP[1<<2];
    // freopen("bank.in","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    cin >> N >> M;
    int salaries[N], notes[M];
    loop(i,N) {
        cin >> salaries[i];
    }
    loop(i,M) {
        cin >> notes[i];
    }
    bool solved = false;
    loop(bm,1<<M) {
        bool works = false;
        if (!bm) {
            DP[bm] = MP(0,salaries[0]);
            continue;
        }
        loop(ind,M) {
            if (bm&1<<ind) {
                int prev = bm^1<<ind;
                if (DP[prev].S==0) {
                    if (salaries[DP[prev].F+1]>=notes[ind]) {
                        DP[bm] = MP(DP[prev].F+1,salaries[DP[prev].F+1]-notes[ind]);
                        works = true;
                    }
                } else if (DP[prev].F>=0 && notes[ind]<=DP[prev].S) {
                    DP[bm] = MP(DP[prev].F,DP[prev].S-notes[ind]);
                    works = true;
                }
            }
            if (works) break;
        }
        if (!works) {
            DP[bm] = MP(-1,-1);
        }
        if (DP[bm] == MP(N-1,0)) {
            solved = true;
            cout << "YES";
            break;
        }
    }
    if (!solved) cout << "NO";
}