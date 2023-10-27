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

vector<vi> popGrid(5,vi(5,0));
int offices[5];
int bestLocs[5];
int best;

int cost() {
    int returned=0;
    loop(x,5) {
        loop(y,5) {
            // printf("x,y,pop: %d,%d,%d\n",x,y,popGrid[x][y]);
            if (popGrid[x][y]>0) {
                int dist = INF;
                loop(offIndex,5) {
                    dist = min(dist,abs(x-(offices[offIndex]/5))+abs(y-(offices[offIndex]%5)));
                }
                dist *= popGrid[x][y];
                returned += dist;
            }
        }
    }
    return returned;
}

void iterate(int numChosen) {
    if (numChosen == 5) {
        int curr_cost = cost();
        if (curr_cost < best) {
            copy(offices,offices+5,bestLocs);
            best = curr_cost;
            // printf("best: %d\n",best);
        }
    } else {
        int start = (!numChosen) ? 0 : offices[numChosen-1]+1;
        iloop(nextOffice,start,25) {
        offices[numChosen] = nextOffice;
        iterate(numChosen+1);
        }
    }
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sloop(elem,popGrid) elem.clear();

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        best = INF;
        int locs, x, y, pop;
        cin >> locs;
        loop(i,5) loop(j,5) popGrid[i][j] = 0;
        loop(i,locs) {
            cin >> x >> y >> pop;
            popGrid[x][y] = pop;
        }
        iterate(0);
        loop(i,5){
            cout << bestLocs[i] << ((i==4)?"\n":" ");
        }
    }
}