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

const void MYcout(int pageNum,int pages) {
    if (pageNum <= pages) cout << pageNum;
    else cout << "Blank";
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int pages;
    while (true) {
        cin >> pages;
        if (!pages) {
            break;
        }
        cout << "Printing order for " << pages << " pages:\n";
        int sheets = (pages+3)/4;
        loop(sheetNum,sheets) {
            int FL,FR,BL,BR;
            FL = 4*sheets-2*sheetNum;
            FR = 2*sheetNum + 1;
            BL = 2*sheetNum + 2;
            BR = 4*sheets-2*sheetNum-1;
            cout << "Sheet " << sheetNum+1 << ", front: ";
            MYcout(FL,pages);
            cout << ", ";
            MYcout(FR,pages);
            cout << "\n";
            if (pages != 1) {
                cout << "Sheet " << sheetNum+1 << ", back : ";
                MYcout(BL,pages);
                cout << ", ";
                MYcout(BR,pages);
                cout << "\n";
            }
        }
    }
}