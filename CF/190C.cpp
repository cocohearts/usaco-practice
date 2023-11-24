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

    int numCases; cin >> numCases;
    loop(caseNum,numCases) {
        int n; cin >> n;
        int myMin = INF, myMax = 0;
        int newV;
        loop(i,n) {
            cin >> newV;
            myMin = min(newV,myMin);
            myMax = max(newV,myMax);
        }
        vi chosen;
        while (myMin != myMax) {
            --myMax;
            chosen.PB(myMax);
            myMin = (myMax+myMin)/2;
        }
        cout << chosen.size() << "\n";
        if (chosen.size() && chosen.size() <= n) {
            loop(ind,chosen.size()) {
                cout << chosen[ind];
                if (ind < chosen.size()-1) {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
}