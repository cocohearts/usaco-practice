#include <bits/stdc++.h>
#include <iostream>

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
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        if (caseNum > 0) {
            cout << "\n";
        }
        int size;
        cin >> size;
        string makers[size];
        int lowers[size];
        int uppers[size];
        string maker;
        int lower,upper;
        loop(i,size) {
            cin >> maker >> lower >> upper;
            makers[i]=maker;
            lowers[i]=lower;
            uppers[i]=upper;
        }
        int query,queries;
        cin >> queries;
        string answer;
        loop(i,queries) {
            cin >> query;
            bool found = false;
            string maker;
            loop(myIndex,size) {
                if (lowers[myIndex]<=query && uppers[myIndex]>=query) {
                    if (found) {
                        found=false; break;
                    }
                    else {
                        found=true; maker=makers[myIndex];
                    }
                }
            }
            answer = found ? maker : "UNDETERMINED";
            cout << answer << "\n";
        }
    }
}