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
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    cin >> N >> M;
    vector<ll> DP(N+1,0);
    DP[0] = 1;

    vector<bool> primes(N+1,true);
    primes[0] = primes[1] = false;
    loop(i,N+1) {
        if (primes[i]) {
            int comp = 2*i;
            while (comp <= N) {
                primes[comp] = false;
                comp += i;
            }
        }
    }
    loop(prime,N+1) {
        if (primes[prime]) {
            for (int ind = N; ind>0; --ind) {
                ll pow = prime;
                while (pow <= ind) {
                    DP[ind] += pow * DP[ind-pow];
                    DP[ind] %= M;
                    pow *= prime;
                    pow %= M;
                }
            }
        }
    }
    int answer = 0;
    loop(ind,N+1) {
        answer += DP[ind];
        answer %= M;
    }
    cout << answer;
}