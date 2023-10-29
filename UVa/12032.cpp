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

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int rungs;
        cin >> rungs;
        vi ladder(1,0);
        int rung;
        loop(i,rungs) {
            cin >> rung;
            ladder.PB(rung);
        }
        int bot,K,mid,top;
        bot = 1; top = *(ladder.end()-1);
        while (top>bot) {
            mid = (top+bot)/2;
            K = mid;
            bool success = true;
            int dist;
            for(auto&& rungIt = ladder.begin(); rungIt != ladder.end()-1; ++rungIt) {
                dist = *(rungIt+1) - *(rungIt);
                if (dist>K) {
                    success = false;
                    break;
                } else if (dist == K) {
                    --K;
                }
            }
            if (success) {
                top = mid;
            } else {bot = mid+1;}
        }
        cout << "Case " << caseNum+1 << ": " << bot << "\n";
    }
}