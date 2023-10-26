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

    int M;
    while (cin >> M) {
        int arr[M][M];
        char color;
        loop(i,M) {
            // cin >> color;
            loop(j,M) {
                cin >> color;
                arr[i][j] = color-'0';
            }
        }
        int maxDist = 0;
        loop(i,M) {
            loop(j,M) {
                int dist = INF;
                if (arr[i][j]==1) {
                    loop(k,M) {
                        loop(l,M) {
                            if (arr[k][l]==3) {
                                dist = min(dist,abs(i-k)+abs(j-l));
                            }
                        }
                    }
                    maxDist = max(maxDist,dist);
                }
                
            }
        }
        cout << maxDist << "\n";
    }
}