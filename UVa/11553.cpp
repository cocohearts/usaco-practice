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

vector<bool> picked;
vector<vi> grid;
vi permutation;
int minScore;
int n;

void iterate() {
    if (permutation.size()==n) {
        int score=0;
        loop(i,n) {
            score += grid[permutation[i]][i];
        }
        if (score<minScore) minScore=score;
    } else {
        loop(i,n) {
            if (!picked[i]) {
                permutation.PB(i);
                picked[i]=true;
                iterate();
                picked[i]=false;
                permutation.pop_back();
            }
        }
    }
}

int main() {
    // equiv. over all rook placings on grid, minimize sum
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        cin >> n;
        int elem;
        loop(i,n) {
            vi newRow(n);
            loop(j,n) {
                cin >> elem;
                newRow[j] = elem;
            }
            grid.PB(newRow);
        }
        minScore = INF;
        picked.resize(n);
        fill(picked.begin(),picked.end(),false);
        iterate();
        cout << minScore << "\n";
        grid.clear();
    }
}