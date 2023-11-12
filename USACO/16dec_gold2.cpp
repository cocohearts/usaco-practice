#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 2e9
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int endG[1001][1001];
int endH[1001][1001];

int dist(ii p1,ii p2) {
    return pow((p1.F-p2.F),2) + pow((p1.S-p2.S),2);
}

int main() {
    freopen("checklist.in","r",stdin);
    freopen("checklist.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H,G;
    // arr[G][H] is the mincost for covering G guernseys, H holsteins, ending at arr
    vii hol, gue;
    int x,y;
    cin >> H >> G;
    loop(i,H) {
        cin >> x >> y;
        hol.PB(MP(x,y));
    }
    loop(i,G) {
        cin >> x >> y;
        gue.PB(MP(x,y));
    }
    loop(g,G+1) loop(h,H+1) {
        if (g==0 && h<=1) {
            endG[g][h] = endH[g][h] = 0;
            continue;
        } 
        if (h==0 && g>0) {
            endG[g][h] = endH[g][h] = INF;
            continue;
        }
        int answerG = INF, answerH = INF;
        if (g>1) {
            answerG = min(answerG, endG[g-1][h] + dist(gue[g-2],gue[g-1]));
        }
        if (h>1) {
            answerH = min(answerH, endH[g][h-1] + dist(hol[h-2],hol[h-1]));
        }
        if (g&&h) {
            int lastStep = dist(hol[h-1],gue[g-1]);
            answerG = min(answerG, endH[g-1][h] + lastStep);
            answerH = min(answerH, endG[g][h-1] + lastStep);
        }
        endG[g][h] = answerG; endH[g][h] = answerH;
    }
    // loop(g,G+1) {
    //     loop(h,H+1) {
    //         cerr << endG[g][h] << " ";
    //     }
    //     cerr << "\n";
    // }
    // loop(g,G+1) {
    //     loop(h,H+1) {
    //         cerr << endH[g][h] << " ";
    //     }
    //     cerr << "\n";
    // }
    cout << endH[G][H];
}