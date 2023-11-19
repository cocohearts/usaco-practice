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

class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
    }
};

int main() {
    Solution myObj;
    vi heights {6,4,8,5,2,7};
    vector<vi> queries {{0,1},{0,3},{2,4},{3,4},{2,2}};
    vi ans = myObj.leftmostBuildingQueries(heights,queries);
    sloop(item,ans) {
        cout << item << " ";
    }
    cout << "\n";
}