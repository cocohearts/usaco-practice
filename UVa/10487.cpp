#include <bits/stdc++.h>
#include <iostream>
#include <set>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
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

    int caseNum = 0;
    int setSize,queries,query;
    while (cin >> setSize) {
        ++caseNum;
        if (!setSize) break;
        printf("Case %u:\n",caseNum);
        int items[setSize];
        int newElem;
        loop(i,setSize) {
            cin >> newElem;
            items[i] = newElem;
        }
        cin >> queries;
        loop(k,queries) {
            cin >> query;
            int closest = INF;
            int testSum;
            loop(i,setSize) {
                if (closest==query) break;
                for (int j=i+1; j<setSize; ++j) {
                    testSum = items[i] + items[j];
                    if (abs(testSum - query) < abs(closest - query)) {
                        closest = testSum;
                    }
                }
            }
            printf("Closest sum to %d is %d.\n",query,closest);
        }
    }
}