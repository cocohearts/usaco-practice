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

int V,E;
vector<bool> chosenBool;
vi chosen;
int best;
vi bestChosen;
vi match = {5,7,8};

int neighbor;

void iterate(vector<vi> adjList, int v) {
    if (chosen.size()>best) {
        bestChosen = chosen;
        best = chosen.size();
    }
    iloop(nextV,v,V) {
        bool works = true;
        itloop(neighborIt,adjList[nextV]) {
            if (chosenBool[*neighborIt]) {
                works = false;
                break;
            }
        }
        if (works) {
            chosenBool[nextV] = true;
            chosen.PB(nextV);
            if (chosen == match) {
                int a = 1;
            }
            iterate(adjList,nextV+1);
            chosenBool[nextV] = false;
            chosen.pop_back();
        }
    }
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        cin >> V >> E;
        vector<vi> adjList;
        adjList.resize(V);
        int a,b;
        loop(i,E) {
            cin >> a >> b;
            adjList[a-1].PB(b-1);
            adjList[b-1].PB(a-1);
        }
        best = 0;
        bestChosen.clear();
        chosenBool.resize(V);
        iterate(adjList,0);
        cout << best << "\n";
        loop(i,best) {
            cout << bestChosen[i]+1;
            cout << ((i!=best-1) ? " " : "\n");
        }
    }
}