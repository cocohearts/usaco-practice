#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    while (true) {
        cin >> N >> M;
        if (N+M==0) break;
        vector<vi> gridProp;
        int prop;
        vi newRow(M);
        loop(i,N) {
            loop(j,M) {
                cin >> prop;
                newRow[j] = prop;
            }
            gridProp.PB(newRow);
        }
        vector<vi> diags;
        iloop(L,1-N,M) {
            vi diag;
            loop(x,N) {
                int y = x+L;
                if (0<=y && y<M) {
                    diag.PB(gridProp[x][y]);
                }
            }
            diags.PB(diag);
        }
        int Q;
        cin >> Q;
        int L,U;
        loop(queryNum,Q) {
            cin >> L >> U;
            int best=0;
            sloop(diag,diags) {
                best = max(best,(int)(upper_bound(diag.begin(),diag.end(),U)-lower_bound(diag.begin(),diag.end(),L)));
            }
            cout << best << "\n";
        }
        cout << "-\n";
    }
}