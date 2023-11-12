#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 2000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int DP[1000][1000];

int main() {
    freopen("nocross.in","r",stdin);
    freopen("nocross.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vi left,right;
    int id;
    loop(i,N) {
        cin >> id;
        left.PB(id);
    }
    loop(i,N) {
        cin >> id;
        right.PB(id);
    }
    loop(i,N+1) loop(j,N+1) {
        if (!(i&&j)) {
            DP[i][j]=0;
            continue;
        }
        int answer = 0;
        answer = max(answer,DP[i-1][j]);
        answer = max(answer,DP[i][j-1]);
        if (abs(left[i-1]-right[j-1])<=4) {
            answer = max(answer,DP[i-1][j-1]+1);
        }
        DP[i][j] = answer;
    }
    cout << DP[N][N];
}