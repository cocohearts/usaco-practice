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

int FJ[1000], FP[1000];
int DP[10][1000][1000];
int Pr[10][1000][1000];

int main() {
    freopen("input","r",stdin);
    // freopen("team.in","r",stdin);
    // freopen("team.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P = 1000000007;

    int N,M,K;
    cin >> N >> M >> K;
    // int FJ[N], FP[M];
    int score;
    loop(i,N) {
        cin >> score;
        FJ[i] = score;
    }
    loop(i,M) {
        cin >> score;
        FP[i] = score;
    }
    sort(FJ,FJ+N);
    sort(FP,FP+M);
    loop(cows,K) {
        if (cows==0) {
            loop(i,M) {
                bool beat = false;
                loop(j,N) {
                    if (beat) {
                        DP[cows][i][j] = 1;
                        continue;
                    }
                    if (FJ[j] > FP[i]) {
                        beat = true;
                        DP[cows][i][j] = 1;
                    } else {
                        DP[cows][i][j] = 0;
                    }
                }
            }
        } else {
            loop(i,N) {
                int sum = 0;
                loop(j,M) {
                    if (!(i&&j)) {
                        Pr[cows][i][j] = 0;
                    } else {
                        sum += DP[cows-1][i-1][j-1];
                        sum %= P;
                        Pr[cows][i][j] = sum;
                    }
                }
            }
            loop(j,M) {
                int sum = 0;
                loop(i,N) {
                    sum += Pr[cows][i][j];
                    sum %= P;
                    if (FJ[j] > FP[i]) {
                        DP[cows][i][j] = sum;
                    } else {
                        DP[cows][i][j] = 0;
                    }
                }
            }
        }
    }
    int sum = 0;
    loop(i,N) {
        loop(j,M) {
            sum += DP[K-1][i][j];
            sum %= P;
        }
    }

    // loop(cows,K) {
    //     loop(i,M) {
    //         loop(j,N) {
    //             cerr << DP[cows][i][j] << " ";
    //         }
    //         cerr << "\n";
    //     }
    //     cerr << "\n";
    // }

    cout << sum;
}