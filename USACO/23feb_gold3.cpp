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

// change L to 300
const int L = 300;
int DP[L][L+1][18][19][3];
int nums[L];

void fill(int anses[][L], int N, ll X) {
    ll pow = 1L;
    ll Y = X;
    int Xarr[18];
    loop(ind,18) {
        Xarr[ind] = Y%10;
        Y /= 10L;
    }
    // interval size is sSi
    loop(sSi,19) {
        // interval size is iSi+1
        loop(iSi,N) {
            loop(sSt,19-sSi) {
                loop(iSt,N-iSi) {
                    int sEn = sSt+sSi;
                    int iEn = iSt+iSi;

                    if (!sSi) {
                        // substring is empty; only choice is to drop all digits
                        DP[iSt][iEn][sSt][sEn][0] = 0;
                        DP[iSt][iEn][sSt][sEn][1] = 1;
                        DP[iSt][iEn][sSt][sEn][2] = 0;
                        continue;
                    }

                    int Xfd = Xarr[sSt];
                    int Xld = Xarr[sEn-1];
                    int dig = nums[iEn];

                    if (!iSi) {
                        // only have one digit; must place
                        DP[iSt][iEn][sSt][sEn][0] = 0;
                        DP[iSt][iEn][sSt][sEn][1] = 0;
                        DP[iSt][iEn][sSt][sEn][2] = 0;
                        if (sSi==1) {
                            int ind;
                            if (dig < Xld) {
                                ind = 0;
                            } else if (dig == Xld) {
                                ind = 1;
                            } else {
                                ind = 2;
                            }
                            DP[iSt][iEn][sSt][sEn][ind] += 2;
                        }
                        continue;
                    }

                    // ignore new digit
                    DP[iSt][iEn][sSt][sEn][0] = DP[iSt][iEn-1][sSt][sEn][0];
                    DP[iSt][iEn][sSt][sEn][1] = DP[iSt][iEn-1][sSt][sEn][1];
                    DP[iSt][iEn][sSt][sEn][2] = DP[iSt][iEn-1][sSt][sEn][2];

                    // add new digit to end
                    DP[iSt][iEn][sSt][sEn][0] += DP[iSt][iEn-1][sSt+1][sEn][0];
                    DP[iSt][iEn][sSt][sEn][0] %= MOD;
                    DP[iSt][iEn][sSt][sEn][2] += DP[iSt][iEn-1][sSt+1][sEn][2];
                    DP[iSt][iEn][sSt][sEn][2] %= MOD;
                    if (dig < Xfd) {
                        DP[iSt][iEn][sSt][sEn][0] += DP[iSt][iEn-1][sSt+1][sEn][1];
                        DP[iSt][iEn][sSt][sEn][0] %= MOD;
                    } else {
                        if (dig == Xfd) {
                            DP[iSt][iEn][sSt][sEn][1] += DP[iSt][iEn-1][sSt+1][sEn][1];
                            DP[iSt][iEn][sSt][sEn][1] %= MOD;
                        } else {
                            DP[iSt][iEn][sSt][sEn][2] += DP[iSt][iEn-1][sSt+1][sEn][1];
                            DP[iSt][iEn][sSt][sEn][2] %= MOD;
                        }
                    }

                    // add new digit to front
                    if (dig <= Xld) {
                        DP[iSt][iEn][sSt][sEn][0] += DP[iSt][iEn-1][sSt][sEn-1][0];
                        DP[iSt][iEn][sSt][sEn][0] %= MOD;
                        if (dig == Xld) {
                            DP[iSt][iEn][sSt][sEn][1] += DP[iSt][iEn-1][sSt][sEn-1][1];
                            DP[iSt][iEn][sSt][sEn][1] %= MOD;
                            DP[iSt][iEn][sSt][sEn][2] += DP[iSt][iEn-1][sSt][sEn-1][2];
                            DP[iSt][iEn][sSt][sEn][2] %= MOD;
                        } else {
                            DP[iSt][iEn][sSt][sEn][0] += DP[iSt][iEn-1][sSt][sEn-1][1];
                            DP[iSt][iEn][sSt][sEn][0] %= MOD;
                            DP[iSt][iEn][sSt][sEn][0] += DP[iSt][iEn-1][sSt][sEn-1][2];
                            DP[iSt][iEn][sSt][sEn][0] %= MOD;
                        }
                    } else {
                        DP[iSt][iEn][sSt][sEn][2] += DP[iSt][iEn-1][sSt][sEn-1][0];
                        DP[iSt][iEn][sSt][sEn][2] %= MOD;
                        DP[iSt][iEn][sSt][sEn][2] += DP[iSt][iEn-1][sSt][sEn-1][1];
                        DP[iSt][iEn][sSt][sEn][2] %= MOD;
                        DP[iSt][iEn][sSt][sEn][2] += DP[iSt][iEn-1][sSt][sEn-1][2];
                        DP[iSt][iEn][sSt][sEn][2] %= MOD;
                    }
                }
            }
        }
    }
    int dig_len = 0; pow = 1;
    while (pow<=X) {
        ++dig_len; pow*=10;
    }
    loop(iSt,N) {
        loop(iEn,N) {
            int ans = 0;
            loop(sEn,19) {
                ans += DP[iSt][iEn][0][sEn][0];
                ans += DP[iSt][iEn][0][sEn][1];
                if (sEn<dig_len) {
                    ans += DP[iSt][iEn][0][sEn][2];
                }
            }
            anses[iSt][iEn] = ans;
        }
    }
}


int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll A,B;
    cin >> N >> A >> B;
    loop(i,N) {
        cin >> nums[i];
    }

    int Aanses[L][L];
    int Banses[L][L];
    loop(i,L) loop(j,L) {
        Aanses[i][j] = Banses[i][j] = 0;
    }

    fill(Aanses,N,A-1);
    fill(Banses,N,B);
    int Q;
    cin >> Q;
    int m,n;
    loop(i,Q) {
        cin >> m >> n;
        --m; --n;
        int ans = Banses[m][n]-Aanses[m][n];
        ans %= MOD;
        if (ans<0) ans += MOD;
        cout << ans << "\n";
    }
}