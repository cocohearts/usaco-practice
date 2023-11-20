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

bool arr[39][3];

ll DP[39][2];

ll solve(ll x) {
    ll pow = 1L;
    loop(pos,39) {
        DP[pos][0] = 0;
        DP[pos][1] = 0;
        loop(gt,2) {
            loop(dig,3) {
                if (arr[pos][dig]) {
                    if (!pos) {
                        if ((dig>x%3L)==gt) {
                            ++DP[pos][gt];
                        }
                        continue;
                    }

                    int x_dig = (x/pow)%3L;
                    if ((dig > x_dig)==gt) {
                        if (!gt) {
                            if (dig < x_dig) {
                                DP[pos][gt] += DP[pos-1][0]+DP[pos-1][1];
                            } else {
                                DP[pos][gt] += DP[pos-1][gt];
                                DP[pos][1] += DP[pos-1][1];
                            }
                        }
                        if (gt) {
                            DP[pos][gt] += DP[pos-1][0]+DP[pos-1][1];
                        }
                    }
                }
            }
        }
        pow *= 3L;
    }
    return DP[38][0];
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q; cin >> Q;
    ll d,x,y;
    ll powers[40];
    powers[0]=1;
    loop(ind,39) {
        powers[ind+1] = 3*powers[ind]+1;
    }
    loop(caseNum,Q) {
        cin >> d >> x >> y;
        if (x>y) {
            ll z = y;
            y = x;
            x = z;
        }
        ll diff = y-x;
        if (diff%2) {
            cout << "0\n";
            continue;
        }
        diff /= 2;
        diff += powers[38];

        loop(ind,39) {
            arr[ind][0] = (diff%3)>=1;
            arr[ind][1] = (diff%3)==1;
            arr[ind][2] = (diff%3)<=1;
            diff /= 3;
        }

        ll answer = solve(x+d) - solve(x-1);
        cout << answer << "\n";
    }
}