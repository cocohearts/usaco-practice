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

string names[8] = {
    "RAKIBUL",
    "ANINDYA",
    "MOSHIUR",
    "SHIPLU",
    "KABIR",
    "SUNNY",
    "OBAIDA",
    "WASI"
};

string gridString="OBIDAIBKRRKAULHISPSADIYANNOHEISAWHIAIRAKIBULSMFBINTRNOUTOYZIFAHLEBSYNUNEEMOTIONAL";

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char grid[9][9];

    loop(i,81) {
        grid[i/9][i%9] = gridString[i];
    }

    sloop(name, names) {
        int count = 0;
        int len = name.size();
        set<char> letters;
        sloop(nameChar, name) {
            letters.insert(nameChar);
        }
        set<char> horiletters;
        set<char> vertletters;
        loop(i,10-len) {
            loop(j,10-len) {
                horiletters.clear();
                vertletters.clear();
                loop(disp,len) {
                    horiletters.insert(grid[i+disp][j]);
                    vertletters.insert(grid[i][j+disp]);
                }
                if (horiletters==letters) {++count;}
                if (vertletters==letters) {++count;}
            }
        }
        if (count == 2) {
            cout << name << "\n";
        }
    }
}