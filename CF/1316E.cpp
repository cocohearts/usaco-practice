#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 2000000000
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

    int n,p,k;
    cin >> n >> p >> k;

    ii audience[n];
    int position[n][p];
    loop(i,n) {
        cin >> audience[i].F;
        audience[i].S = i;
    }
    loop(i,n) {
        loop(j,p) {
            cin >> position[i][j];
        }
    }
    sort(audience,audience+n);
    // descending order
    int topBest[p][p];
    int botBest[p][p];

    loop(pos,p) {
        vi top(0,0), bot(0,0);
        loop(ind,k+p) {
            int val = position[audience[ind].S][pos];
            if (!top.size()) {
                top.PB(ind);
            } else {
                loop(comp,top.size()) {
                    if (position[audience[top[comp]].S][pos]<val) {
                        top.insert(top.begin()+comp,ind);
                        if (top.size()>p) {
                            top.pop_back();
                        }
                    } else if (top.size()<p && val < *top.rend()) {
                        top.insert(top.end(),ind);
                    }
                }
            }
        }
        iloop(ind,k+p,n) {
            int val = position[audience[ind].S][pos];
            if (!bot.size()) {
                bot.PB(ind);
            } else {
                loop(comp,bot.size()) {
                    if (position[audience[bot[comp]].S][pos]<val) {
                        bot.insert(bot.begin()+comp,ind);
                        if (bot.size()>p) {
                            bot.pop_back();
                        }
                    } else if (bot.size()<p && val < *bot.rend()) {
                        bot.insert(bot.end(),ind);
                    }
                }
            }
        }

        loop(ind,p) {
            topBest[pos][ind] = top[ind];
            botBest[pos][ind] = bot[ind];
        }
    }
    // 
    ii DP[1<<p];
    


}