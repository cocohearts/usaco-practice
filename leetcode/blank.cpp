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
        int n = heights.size();
        int logn=0;
        while (n>1<<logn) {
            ++logn;
        }
        n = heights.size();
        int arr[n][logn+1];

        loop(exp,logn+1) {
            loop(ind,n) {
                if (!exp) {
                    arr[ind][exp] = heights[ind];
                    continue;
                }
                arr[ind][exp] = arr[ind][exp-1];
                if (ind+(1<<(exp-1))<n) {
                    arr[ind][exp] = max(arr[ind][exp],arr[ind+(1<<(exp-1))][exp-1]);
                }
            }
        }
        // loop(i,n) {
        //     loop(j,logn+1) {
        //         cerr << arr[i][j] << " ";
        //     }
        //     cerr << "\n";
        // }
        vi ans(queries.size());
        int A,B,val;
        loop(ind,queries.size()) {
            A = min(queries[ind][0],queries[ind][1]); 
            B = max(queries[ind][0],queries[ind][1]); 
            if (heights[B]>=heights[A]) {
                ans[ind] = B;
                continue;
            }

            val = heights[A];
            // find first index after B whose value is at least val
            int search = B; 
            int exp = logn;
            if (arr[B][exp]<val) {
                ans[ind] = -1; continue;
            }
            while (exp > 0) {
                if (arr[search][exp-1]<val) {
                    search += 1<<(exp-1);
                }
                --exp;
            }
            ans[ind] = search;
        }
        return ans;
    }
};

// int main() {
//     Solution myObj;
//     vi heights {6,4,8,5,2,7};
//     vector<vi> queries {{0,1},{0,3},{2,4},{3,4},{2,2}};
//     vi ans = myObj.leftmostBuildingQueries(heights,queries);
//     sloop(item,ans) {
//         cout << item << " ";
//     }
//     cout << "\n";
// }