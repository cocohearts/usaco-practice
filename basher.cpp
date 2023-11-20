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

int x,y,d,m;

int solve(int x) {
    int ans=0;
    loop(i,x) {
        cout << ans << "\n";
        if (i%m) continue;
        string s = to_string(i);
        bool broke = false;
        loop(ind,s.size()) {
            if ((ind%2) != (int)(s[ind]==d+'0')) {
                broke = true;
                break;
            }
        }
        if (!broke) {
            ++ans;
            // cout << i << "\n";
        } 
    }
    return ans;
}

int main() {
    freopen("CF/input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> d >> x >> y;
    // int ans = solve(y)-solve(x-1);
    // cout << ans << "\n";
    // int pow=1;
    // loop(i,6) {
    //     cout << pow << "\n";
    //     cout << solve(pow) << "\n";
    //     pow *= 10;
    // }
    solve(1000000);
}