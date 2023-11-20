#include <bits/stdc++.h>
#include <iostream>

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

int DP[2000][2000][2][2];
int m,d;
int N;

int solve(int X[2000]) {
    int answers = 0;
    // DP inclusive this time
    int pow = 1;
    loop(pos,N) {
        if (pos) {
            pow *= 10;
            pow %= m;
        }
        loop(res,m) {
            loop(par,2) {
                DP[pos][res][0][par] = 0;
                DP[pos][res][1][par] = 0;
                loop(dig,10) {
                    if ((par+pos)%2==0 && dig!=d) {
                        continue;
                    }
                    if ((par+pos)%2==1 && dig==d) {
                        continue;
                    }
                    if (!pos) {
                        if (dig%m==res) {
                            ++DP[pos][res][(int)(dig>X[N-1])][par];
                        }
                        continue;
                    }
                    int prevRes = res-dig*pow;
                    prevRes %= m;
                    if (prevRes<0) {
                        prevRes += m;
                    }
                    if (dig <= X[N-1-pos]) {
                        DP[pos][res][0][par] += DP[pos-1][prevRes][0][par];
                        DP[pos][res][0][par] %= MOD;
                        if (dig == X[N-1-pos]) {
                            DP[pos][res][1][par] += DP[pos-1][prevRes][1][par];
                            DP[pos][res][1][par] %= MOD;
                        } else {
                            DP[pos][res][0][par] += DP[pos-1][prevRes][1][par];
                            DP[pos][res][0][par] %= MOD;
                        }
                    } else {
                        DP[pos][res][1][par] += DP[pos-1][prevRes][0][par];
                        DP[pos][res][1][par] %= MOD;
                        DP[pos][res][1][par] += DP[pos-1][prevRes][1][par];
                        DP[pos][res][1][par] %= MOD;
                    }
                    if (res==0 && par+pos%2 && dig==0) {
                        answers -= DP[pos][0][0][par];
                        answers %= MOD;
                        if (pos<N-1) {
                            answers -= DP[pos][0][1][par];
                            answers %= MOD;
                        }
                    }
                }
                if (res == 0 && (par+pos)%2) {
                    answers += DP[pos][0][0][par];
                    answers %= MOD;
                    if (pos<N-1) {
                        answers += DP[pos][0][1][par];
                        answers %= MOD;
                    }
                }
            }
        }
    }
    return answers;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sa, sb;
    cin >> m >> d >> sa >> sb;
    N = sa.size();
    int a[2000], b[2000];
    loop(i,N) {
        a[i] = sa[i] - '0';
        b[i] = sb[i] - '0';
    }

    int ans = solve(b) - solve(a);
    // check if a works
    int pow = 1;
    int sum = 0;
    loop(ind,N) {
        sum += pow*a[N-1-ind];
        sum %= m;
        pow *= 10;
        pow %= m;
    }
    if (sum%m==0) {
        bool broke = false;
        loop(ind,N) {
            if ((ind%2)!=(int)(a[ind]==d)) {
                broke = true;
            }
        }
        if (!broke) {
            ++ans;
        }
    }

    ans %= MOD;
    if (ans<0) ans += MOD;
    cout << ans;
}