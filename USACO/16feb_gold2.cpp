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
    // freopen("input","r",stdin);
    freopen("cbarn2.in","r",stdin);
    // freopen("myoutput","w",stdout);
    freopen("cbarn2.out","w",stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    cin >> n >> k;
    vi rooms(n);
    int r;
    loop(i,n) {
        cin >> r;
        rooms[i]=r;
    }

    int lrBest[n][n][max(k-1,1)];
    loop(i,n) {
        loop(j,n) {
            loop(l,max(k-1,1)) {
                lrBest[i][j][l] = INT_MAX;
            }
        }
    }

    loop(i,n) {
        int cost = 0;
        iloop(j,i+1,n+i+1) {
            lrBest[i][(j%n)][0] = cost;
            cost += rooms[(j%n)]*(j-i);
            cerr << i << " " << j << " " << cost << "\n";
        }
    }
    int answer = INT_MAX;
    iloop(doors,1,k-1) {
        loop(i,n) {
            iloop(j,i+doors+1,n) {
                int bestCost = INT_MAX;
                iloop(R,i+doors,j) {
                    bestCost = min(bestCost,lrBest[i][R][doors-1]+lrBest[R][j][0]);
                }
                lrBest[i][j][doors] = bestCost;
            }
        }
    }
    loop(i,n) {
        iloop(j,i+k-1,n) {
            answer = min(answer,lrBest[i][j][k-2]+lrBest[j][i][0]);
        }
    }
    if (k==1) {
        answer = INT_MAX;
        loop(i,n) {
            answer = min(answer,lrBest[i][i][0]);
        }
    }
    cout << answer;
}