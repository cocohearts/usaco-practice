#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <map>

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
    freopen("cowmbat.in","r",stdin);
    freopen("cowmbat.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string alph = "abcdefghijklmnopqrstuvwxyz";
    map<char,int> alphMap;
    loop(i,26) {
        alphMap[alph[i]] = i;
    }

    int N,M,K;
    cin >> N >> M >> K;
    string combo;
    cin >> combo;
    int initCosts[M][M];
    int cost;
    loop(i,M) {
        loop(j,M) {
            cin >> cost;
            initCosts[i][j] = cost;
        }
    }
    // Dijkstra's cost reduction
    int bestCosts[M][M];
    vi dist(M);
    vector<bool> visited(M);
    loop(source,M) {
        fill(dist.begin(),dist.end(),INT_MAX);
        dist[source] = 0;
        fill(visited.begin(),visited.end(),false);
        loop(i,M) {
            int minDist = INT_MAX;
            int minIndex;
            loop(i,M) {
                if (!visited[i] && (dist[i]<minDist)) {
                    minDist = dist[i];
                    minIndex = i;
                }
            }
            visited[minIndex] = true;
            bestCosts[source][minIndex] = minDist;
            loop(nextV,M) {
                dist[nextV] = min(dist[nextV],minDist+initCosts[minIndex][nextV]);
            }
        }
    }

    // loop(i,M) {
    //     loop(j,M) {
    //         cerr << bestCosts[i][j] << " ";
    //     }
    //     cerr << "\n";
    // }
    // cerr << "\n";

    int costs[M][N];
    loop(c,M) {
        int cumCost = 0;
        loop(letterIndex,N) {
            cumCost += bestCosts[alphMap[combo[letterIndex]]][c];
            costs[c][letterIndex] = cumCost;
        }
    }
    // loop(c,M) {
    //     loop(i,N) {
    //         cerr << costs[c][i] << " ";
    //     }
    //     cerr << "\n";
    // }

    int DP[N];
    int prev[M];
    fill(prev,prev+M,0);
    loop(letterInd,N) {
        // cerr << "\n\n" << letterInd << "\n";
        int bestCost = INT_MAX;
        loop(c,M) {
            // cerr << prev[c] << " ";
            bestCost = min(bestCost,prev[c]+costs[c][letterInd]);
            if (letterInd-K+1>=K-1) {
                prev[c] = min(prev[c],DP[letterInd-K+1]-costs[c][letterInd-K+1]);
            }
        }
        // cerr << "\n";
        // cerr << bestCost << "\n";
        DP[letterInd] = bestCost;
    }
    // cerr << "\n";
    // loop(i,N) {
    //     cerr << DP[i] << " ";
    // }
    // cerr << "\n";

    cout << (int)DP[N-1];
}