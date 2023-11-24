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

    int n; cin >> n;
    int nums[n];
    loop(i,n) {
        cin >> nums[i];
    }
    int lefts[n], rights[n];
    int leftm = 0, rightm = 0;
    loop(i,n) {
        lefts[i] = leftm;
        leftm = max(leftm,n-1-i+nums[i]);

        rights[n-1-i] = rightm;
        rightm = max(rightm,nums[n-1-i]+(n-1-i));
    }
    int ans = 2*INF;
    loop(i,n) {
        int cost = max(nums[i],max(lefts[i],rights[i]));
        // if (i) {
        //     cost = max(cost,lefts[i-1]);
        // } if (n-1>i) {
        //     cost = max(cost,rights[i+1]);
        // }
        ans = min(ans,cost);
    }
    cout << ans;
}