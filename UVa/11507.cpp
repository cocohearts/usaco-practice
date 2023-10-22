#include <bits/stdc++.h>
#include <iostream>
#include <map>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)

// pmx is 0,1, pmy is 2,3, pmz is 4,5
// map[dir][bent-2]=newdir
int bendMap[6][4] = {
    {2,3,4,5},
    {3,2,5,4},
    {1,0,2,2},
    {0,1,3,3},
    {4,4,1,0},
    {5,5,0,1}
};

map<string,int> inpMap;

string inpArr[6] = {"+x","-x","+y","-y","+z","-z"};

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    loop(i,6) {
        inpMap[inpArr[i]]=i;
    }

    int L;
    cin >> L;
    while (L != 0) {
        int dir = 0;
        string newDir;
        loop(i,L-1) {
            cin >> newDir;
            if (newDir != "No") {
                dir = bendMap[dir][inpMap[newDir]-2];
            }
        }
        cout << inpArr[dir] << "\n";

        cin >> L;
    }
}