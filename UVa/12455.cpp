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

vector<bool> chosen;
vi bars;
int n,p;

bool iterate(int index) {
    if (!n) return true;
    if (index==p) return false;
    if (iterate(index+1)) return true;
    n-=bars[index];
    if (iterate(index+1)) return true;
    n+=bars[index];
    return false;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        cin >> n >> p;
        int bar;
        loop(i,p) {
            cin >> bar;
            bars.PB(bar);
        }
        string ans = iterate(0) ? "YES" : "NO";
        cout << ans << "\n";
        bars.clear();
    }
}