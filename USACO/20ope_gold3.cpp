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

ll DP[10001][1231];

int main() {
    // freopen("input","r",stdin);
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M;
    cin >> N >> M;
    bool primes[N+1];
    loop(i,N+1) {
        primes[i] = true;
    }
    primes[0] = false;
    primes[1] = primes[2] = true;
    iloop(p,2,N) {
        if (primes[p]) {
            int comp = 2*p;
            while (comp <= N) {
                primes[comp] = false;
                comp += p;
            }
        }
    }
    vi primesArr;
    loop(i,N+1) {
        if (primes[i]) {
            primesArr.PB(i);
        }
    }

    loop(i,N) {
        DP[0][i] = 1;
    }
    int prevPrime[N+1];
    int primeIndex=-1;
    iloop(i,0,N+1) {
        if (primes[i]) {
            ++primeIndex;
        }
        prevPrime[i] = primeIndex;
    }
    prevPrime[0] = INT_MAX;

    iloop(n,1,N+1) {
        DP[n][0] = 1;
        iloop(i,1,primesArr.size()) {
            int m = primesArr[i];
            if (m>n) break;
            ll newVal = DP[n][i-1];
            int newIndex = i;
            if (n>m) newIndex = min(newIndex,prevPrime[n-m]);
            newVal += DP[n-m][newIndex]*m;
            newVal %= M;
            DP[n][i] = newVal;
            // cerr << n << " " << i << " " << newVal << "\n";
        }
    }
    cout << DP[N][primesArr.size()-1];
}