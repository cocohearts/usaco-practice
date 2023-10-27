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

vii pieces;
vector<bool> used;
vi rightEnds(1);
int n,m;
ii myLeft, myRight;

bool iterate() {
    if (rightEnds.size() == n+1) {
        if (rightEnds[n]==myRight.F) {
            return true;
        }
    } else {
        loop(nextInd, m) {
            if (!used[nextInd]) {
                int leftMatch = rightEnds[rightEnds.size()-1];
                if (pieces[nextInd].F == leftMatch) {
                    rightEnds.PB(pieces[nextInd].S);
                    used[nextInd] = true;
                    if (iterate()) {
                        return true;
                    }
                    used[nextInd] = false;
                    rightEnds.pop_back();
                }
                if (pieces[nextInd].S == leftMatch) {
                    rightEnds.PB(pieces[nextInd].F);
                    used[nextInd] = true;
                    if (iterate()) {
                        return true;
                    }
                    used[nextInd] = false;
                    rightEnds.pop_back();
                }
            }
        }
    }
    return false;
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        cin >> n;
        if (!n) break;
        cin >> m;

        int f,s;
        cin >> f >> s;
        myLeft.F=f; myLeft.S=s;
        cin >> f >> s;
        myRight.F=f; myRight.S=s;

        pieces.clear();
        loop(i,m) {
            cin >> f >> s;
            pieces.PB(MP(f,s));
        }
        used.resize(m);
        fill(used.begin(),used.end(),false);

        rightEnds.clear();
        rightEnds.PB(myLeft.S);

        if (iterate()) {
            cout << "YES\n";
        } else cout << "NO\n";
    }
}