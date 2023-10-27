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

// sieve is literal 1-indexed
vector<bool> sieve(60,true);
vi perm(1,1);
int n;
// taken is implicit 0-indexed
vector<bool> taken;

void returnPerm(vi perm) {
    loop(i,n) {
        cout << perm[i];
        if (i!=n-1) {
            cout << " ";
        } else cout << "\n";
    }
}

void iterate() {
    // check at each step
    if (perm.size() == n) {
        if (sieve[perm[0]+perm[n-1]]) {
            returnPerm(perm);
        }
    } else {
        iloop(num,2,n+1) {
            if (!taken[num-1]) {
                if (sieve[num+perm[perm.size()-1]]) {
                    perm.PB(num);
                    taken[num-1] = true;
                    iterate();
                    perm.pop_back();
                    taken[num-1] = false;
                }
            }
        }
    }
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1 is not a prime
    sieve[1]=false;
    iloop(factor,2,16) {
        if (sieve[factor]) {
            iloop(multiplier,2,32/factor+1) {
                sieve[multiplier*factor] = false;
            }
        }
    }

    int caseNum = 0;
    while (cin >> n) {
        ++caseNum;
        if (caseNum > 1) cout << "\n";
        cout << "Case " << caseNum << ":\n";
        taken.resize(n+2);
        fill(taken.begin(),taken.end(),false);
        taken[0] = true;
        iterate();
    }
}