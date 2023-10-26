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

void act(int* elems,vi subset,int k) {
    if (subset.size() == 6) {
        loop(i,6) {
            cout << elems[subset[i]];
            if (i==5) { cout << "\n"; }
            else {cout << " ";}
        }
    }
    int start = 0;
    if (subset.size()) start = subset[subset.size()-1]+1;
    for (int i=start; i<k; ++i) {
        subset.PB(i);
        act(elems,subset,k);
        subset.pop_back();
    }
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    bool started = false;
    while (true) {
        cin >> k;
        if (!k) break;
        if (started) cout << "\n";
        started = true;
        int elem, elems[k];
        loop(i,k) {
            cin >> elem;
            elems[i] = elem;
        }
        vi subset;
        act(elems,subset,k);
    }
}