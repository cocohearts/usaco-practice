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

int DP[6][6+1][18][18][2];
int nums[6];
int Aanses[6][6];
int Banses[6][6];

void fill(int N,int X,int anses[][6]) {
    int digs[18];
    int K = X;
    loop(i,18) {
        digs[17-i] = K%10;
        K /= 10;
    }
    loop(s_si,18) {
        loop(s_st,18-s_si) {
            loop(i_si,N) {
                loop(i_st,N+1-i_si) {
                    int i_en = i_st+i_si;
                    int s_en = s_st+s_si;
                    if (!s_si) {
                        DP[i_st][i_en][s_st][s_si][0] = 1;
                        DP[i_st][i_en][s_st][s_si][1] = 0;
                    } else if (!i_si) {
                        DP[i_st][i_en][s_st][s_si][0] = 0;
                        DP[i_st][i_en][s_st][s_si][1] = 1;
                    } else {
                        DP[i_st][i_en][s_st][s_si][0] = 0;
                        DP[i_st][i_en][s_st][s_si][1] = 0;
                        
                        int first = digs[s_st];
                        int last = digs[s_en-1];
                        DP[i_st][i_en][s_st][s_si][1] += DP[i_st][i_en-1][s_st+1][s_si-1][1];
                        // DP[i_st][i_en][s_st][s_si][1] %= MOD;
                        if (nums[i_en-1]<first) {
                            DP[i_st][i_en][s_st][s_si][1] += DP[i_st][i_en-1][s_st+1][s_si-1][0];
                            // DP[i_st][i_en][s_st][s_si][1] %= MOD;
                        } else if (nums[i_en-1] == first) {
                            DP[i_st][i_en][s_st][s_si][0] += DP[i_st][i_en-1][s_st+1][s_si-1][0];
                            // DP[i_st][i_en][s_st][s_si][0] %= MOD;
                        } 

                        DP[i_st][i_en][s_st][s_si][1] += DP[i_st+1][i_en][s_st][s_si-1][1];
                        // DP[i_st][i_en][s_st][s_si][1] %= MOD;

                        if (nums[i_en-1]<=last) {
                            DP[i_st][i_en][s_st][s_si][1] += DP[i_st][i_en-1][s_st][s_si-1][0];
                            if (nums[i_en-1]==last) {
                                // DP[i_st][i_en][s_st][s_si][0] %= MOD;
                            } else {
                                // DP[i_st][i_en][s_st][s_si][1] %= MOD;
                            }
                        } 

                        DP[i_st][i_en][s_st][s_si][1] += DP[i_st][i_en-1][s_st][s_si][1];
                        // DP[i_st][i_en][s_st][s_si][1] %= MOD;
                        DP[i_st][i_en][s_st][s_si][0] += DP[i_st][i_en-1][s_st][s_si][0];
                        // DP[i_st][i_en][s_st][s_si][0] %= MOD;
                    }
                }
            }
        }
    }
    loop(i,N) {
        loop(j,N+1) {
            // int ans = 0;
            // loop(end,18) {

            // }
            cerr << i << " " << j << "\n";
            cerr << DP[i][j][16][18][0] << " " << DP[i][j][16][18][1] << "\n";
            anses[i][j] = DP[i][j][16][18][0]+DP[i][j][16][18][1] % MOD;
            cerr << anses[i][j] << "\n\n";
        }
    }
}


int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,A,B;
    cin >> N >> A >> B;
    loop(i,N) {
        cin >> nums[i];
    }
    fill(N,A-1,Aanses);
    fill(N,B,Banses);
    int Q;
    cin >> Q;
    int m,n;
    loop(i,Q) {
        cin >> m >> n;
        cout << Banses[m-1][n]-Aanses[m-1][n] << "\n";
    }
}