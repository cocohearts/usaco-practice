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

    int m,n;
    for (int i=0; true; ++i) {
        cin >> n >> m;
        if (!(m+n)) {
            break;
        }
        if (i>0) {
            cout << "\n";
        }
        cout << "Field #" << i+1 << ":\n";
        vector<vector<bool>> minefield(n,vector<bool>(m,false));
        string newRow;
        char newSq;
        loop(i,n) {
            cin >> newRow;
            loop(j,m) {
                newSq = newRow[j];   
                if (newSq == '*') {
                    minefield[i][j] = true;
                }
            }
        }
        loop(i,n) {
            loop(j,m) {
                int count = 0;
                if (!minefield[i][j]) {
                    loop(x,3) {
                        loop(y,3) { 
                            if ((x!=1) || (y!=1)) {
                                int newX = i+x-1;
                                int newY = j+y-1;
                                if ((newX>=0) && (newX<n) && (newY>=0) && (newY<m)) {
                                    count += (minefield[newX][newY]);
                                }
                            }
                        }
                    }
                    cout << count;
                } else cout << '*';
            }
            cout << "\n";
        }
    }
}