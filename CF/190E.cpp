#include <bits/stdc++.h>
#include <iostream>
#include <queue>

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
    
    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int n; cin >> n;
        int weights[n];
        loop(i,n) {
            cin >> weights[i];
        }
        vector<vi> adjL(n,vi(0));
        int u,v;
        loop(i,n-1) {
            cin >> u >> v;
            adjL[u-1].PB(v-1);
            adjL[v-1].PB(u-1);
        }
        // root = 0
        vi BFSArr;
        int parents[n];
        parents[0] = -1;
        queue<int> BFSQ;
        BFSQ.push(0);
        bool visited[n];
        loop(i,n) {
            visited[i] = false;
        }
        int node;
        while (BFSQ.size()) {
            node = BFSQ.front();
            BFSArr.PB(node);
            BFSQ.pop();
            visited[node] = true;
            sloop(nb,adjL[node]) {
                if (visited[nb]) {
                    parents[node] = nb;
                } else {
                    BFSQ.push(nb);
                }
            }
        }
        // BFSArr now reads from bottom-up
        reverse(BFSArr.begin(),BFSArr.end());

        ll best[n];
        loop(ind,n-1) {
            node = BFSArr[ind];
            vi nbs = adjL[node];
            int nbct = nbs.size();
            // take yourself
            best[node] = weights[node];
            if (nbct >= 2) {
                sloop(nb,nbs) {
                    // take exactly one child
                    if (nb != parents[node]) {
                        best[node] = max(best[node],best[nb]);
                    }
                }
                if (nbct >= 3) {
                    // take at least two children
                    vector<ll> children;
                    sloop(nb,nbs) {
                        if (nb != parents[node]) {
                            children.PB(best[nb]);
                        }
                    }
                    sort(children.begin(),children.end(),greater<ll>());
                    ll sum = children[0]+children[1]+weights[node];
                    iloop(cInd,2,children.size()) {
                        if (children[cInd]>0) {
                            sum += children[cInd];
                        } else {
                            break;
                        }
                    }
                    best[node] = max(best[node],sum);
                }
            }
        }
        ll ans = 0;
        loop(topNode,n) {
            // best we can do if topNode is closest to root?
            ll cur = weights[topNode];

            vi nbs = adjL[topNode];
            int nbct = nbs.size();

            vector<ll> children;
            sloop(nb,nbs) {
                if (nb != parents[topNode]) {
                    children.PB(best[nb]);
                }
            }
            sort(children.begin(),children.end(),greater<ll>());
            ll sum = weights[topNode];
            loop(ind,children.size()) {
                sum += children[ind];
                if (ind==1) {
                    sum -= weights[topNode];
                }
                cur = max(cur,sum);
                if (ind==1) {
                    sum += weights[topNode];
                }
            }
            ans = max(ans,cur);
        }
        cout << ans << "\n";
    }
}