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

int main() {
    // freopen("input","r",stdin);
    freopen("spainting.in","r",stdin);
    freopen("spainting.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N,M,K;
    ll P = 1000000007L;
    cin >> N >> M >> K;

    ll DP[N+1];
    ll answer;
    ll power = 1;
    loop(i,N+1) {
        if (i<K) {
            DP[i]=0;
        } else if (i==K) {
            DP[i]=M;
        } else if (i>K) {
            power *= M;
            power %= P;
            answer=M*DP[i-1] + (M-1)*(power-DP[i-K]);
            answer %= P;
            DP[i] = answer;
        }
    }
    int finalAnswer = (int)DP[N];
    if (finalAnswer < 0) finalAnswer += P;
    cout << finalAnswer;
}