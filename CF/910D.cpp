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

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int n;
        cin >> n;
        int a[n],b[n];
        loop(i,n) {
            cin >> a[i];
        }
        loop(i,n) {
            cin >> b[i];
        }
        ll val = 0L;
        int max_alower = INT_MIN;
        int min_ahighe = INT_MAX;
        int max_blower = INT_MIN;
        int min_bhighe = INT_MAX;
        loop(i,n) {
            val += abs(a[i]-b[i]);
            if (a[i]<=b[i]) {
                max_alower = max(max_alower,a[i]);
                min_bhighe = min(min_bhighe,b[i]);
            }
            if (a[i]>=b[i]) {
                min_ahighe = min(min_ahighe,a[i]);
                max_blower = max(max_blower,b[i]);
            }
        }
        int change = max(0,max(max_alower,max_blower) - min(min_ahighe,min_bhighe));
        val += 2*change;
        cout << val << "\n";
    }
}