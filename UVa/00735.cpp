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

vi scores;

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    loop(i,61) {
        if ((i<=20) || (i%2==0 && i/2<=20) || (i%3==0 && i/3<=20)) {
            scores.PB(i);
        }
    }
    scores.PB(50);

    int score;
    while (true) {
        scanf("%d\n",&score);
        if (score<=0) break;
        
        int combos=0;
        int n = scores.size();
        loop(i,n) {
            for (int j=i; j<n; ++j) {
                for (int k=j; k<n; ++k) {
                    if (scores[i]+scores[j]+scores[k]==score) ++combos;
                }
            }
        }
        if (combos) {
            printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n",score,combos);
            int perms=0;
            loop(i,n) {
                loop(j,n) {
                    loop(k,n) {
                        if (scores[i]+scores[j]+scores[k]==score) ++perms;
                    }
                }
            }
            printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n",score,perms);
        } else {printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n",score);}
        printf("**********************************************************************\n");
    }
    printf("END OF OUTPUT\n");
}