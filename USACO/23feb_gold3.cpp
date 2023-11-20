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

int DP[300][300][18][18];

void fill(int N,int X,int **anses) {
    loop(subs_size,18) {
        loop(subs_start,18-subs_size) {
            loop(inte_size,N) {
                loop(inte_start,N-inte_size) {
                    if (!subs_size) {
                        DP[inte_start][inte_start+inte_size][subs_start][subs_size] = 1;
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

    int N,A,B;
    cin >> N >> A >> B;
    int anses[N][N];
    int nums[N];
    loop(i,N) {
        cin >> nums[i];
    }
    int DP[N][N][2];
    loop(A,N) {
        iloop(B,A-1,N) {
            if (B<A) {

            }
        }
    }
}