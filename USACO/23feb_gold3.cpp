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
int PR[L][L+1][18][3];
int NX[L][L+1][18][3];
int nums[L];

void fill(int anses[][L], int N, ll X) {
    ll pow = 1L;
    ll Y = X;
    int Xarr[18];
    loop(ind,18) {
        Xarr[ind] = Y%10;
        Y /= 10L;
    }
    loop(iSt,N) loop(iEn,N) {
        anses[iSt][iEn] = 0;
    }
    int dig_len = 0; pow = 1;
    while (pow<=X) {
        ++dig_len; pow*=10;
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
                        NX[iSt][iEn][sSt][0] = 0;
                        NX[iSt][iEn][sSt][1] = 1;
                        NX[iSt][iEn][sSt][2] = 0;
                        continue;
                    }

                    int Xfd = Xarr[sSt];
                    int Xld = Xarr[sEn-1];
                    int dig = nums[iEn];

                    if (!iSi) {
                        // only have one digit; must place
                        NX[iSt][iEn][sSt][0] = 0;
                        NX[iSt][iEn][sSt][1] = 0;
                        NX[iSt][iEn][sSt][2] = 0;
                        if (sSi==1) {
                            int ind;
                            if (dig < Xld) {
                                ind = 0;
                            } else if (dig == Xld) {
                                ind = 1;
                            } else {
                                ind = 2;
                            }
                            NX[iSt][iEn][sSt][ind] += 2;
                        }
                        continue;
                    }

                    // ignore new digit
                    NX[iSt][iEn][sSt][0] = NX[iSt][iEn-1][sSt][0];
                    NX[iSt][iEn][sSt][1] = NX[iSt][iEn-1][sSt][1];
                    NX[iSt][iEn][sSt][2] = NX[iSt][iEn-1][sSt][2];

                    // add new digit to end
                    NX[iSt][iEn][sSt][0] += PR[iSt][iEn-1][sSt+1][0];
                    NX[iSt][iEn][sSt][0] %= MOD;
                    NX[iSt][iEn][sSt][2] += PR[iSt][iEn-1][sSt+1][2];
                    NX[iSt][iEn][sSt][2] %= MOD;
                    if (dig < Xfd) {
                        NX[iSt][iEn][sSt][0] += PR[iSt][iEn-1][sSt+1][1];
                        NX[iSt][iEn][sSt][0] %= MOD;
                    } else {
                        if (dig == Xfd) {
                            NX[iSt][iEn][sSt][1] += PR[iSt][iEn-1][sSt+1][1];
                            NX[iSt][iEn][sSt][1] %= MOD;
                        } else {
                            NX[iSt][iEn][sSt][2] += PR[iSt][iEn-1][sSt+1][1];
                            NX[iSt][iEn][sSt][2] %= MOD;
                        }
                    }

                    // add new digit to front
                    if (dig <= Xld) {
                        NX[iSt][iEn][sSt][0] += PR[iSt][iEn-1][sSt][0];
                        NX[iSt][iEn][sSt][0] %= MOD;
                        if (dig == Xld) {
                            NX[iSt][iEn][sSt][1] += PR[iSt][iEn-1][sSt][1];
                            NX[iSt][iEn][sSt][1] %= MOD;
                            NX[iSt][iEn][sSt][2] += PR[iSt][iEn-1][sSt][2];
                            NX[iSt][iEn][sSt][2] %= MOD;
                        } else {
                            NX[iSt][iEn][sSt][0] += PR[iSt][iEn-1][sSt][1];
                            NX[iSt][iEn][sSt][0] %= MOD;
                            NX[iSt][iEn][sSt][0] += PR[iSt][iEn-1][sSt][2];
                            NX[iSt][iEn][sSt][0] %= MOD;
                        }
                    } else {
                        NX[iSt][iEn][sSt][2] += PR[iSt][iEn-1][sSt][0];
                        NX[iSt][iEn][sSt][2] %= MOD;
                        NX[iSt][iEn][sSt][2] += PR[iSt][iEn-1][sSt][1];
                        NX[iSt][iEn][sSt][2] %= MOD;
                        NX[iSt][iEn][sSt][2] += PR[iSt][iEn-1][sSt][2];
                        NX[iSt][iEn][sSt][2] %= MOD;
                    }
                }
            }
        }
        loop(iSt,N) {
            loop(iEn,N) {
                int ans = 0;
                ans += NX[iSt][iEn][0][0];
                ans += NX[iSt][iEn][0][1];
                ans %= MOD;
                if (sSi<dig_len) {
                    ans += NX[iSt][iEn][0][2];
                    ans %= MOD;
                }
                anses[iSt][iEn] += ans;
                anses[iSt][iEn] %= MOD;
            }
        }
        loop(iSt,N) {
            loop(iEn,N) {
                loop(sSt,19) {
                    loop(gt,3) {
                        PR[iSt][iEn][sSt][gt] = NX[iSt][iEn][sSt][gt];
                    }
                }
            }
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