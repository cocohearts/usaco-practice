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
        int arr[n];
        loop(i,n) {
            cin >> arr[n-1-i];
        }
        
        int min = arr[0];
        ll ans = 0L;
        loop(i,n) {
            if (min < arr[i]) {
                int q = (arr[i]-1)/min + 1;
                ans += q-1;
                min = arr[i]/q;
            } else {
                min = arr[i];
            }
        }
        cout << ans << "\n";
    }
}