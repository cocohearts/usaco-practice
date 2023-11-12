#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <cstdio>


using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 2000000000
#define MOD 1000000007
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int main() {

    freopen("palpath.in","r",stdin);
    freopen("palpath.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int arr[N][N];
    int Pr[N][N],Ne[N][N];
    char letter;
    loop(i,N) loop(j,N) {
        cin >> letter;
        arr[i][j] = letter-'A';
    }
    if (arr[0][0]!=arr[N-1][N-1]) {
        cout << 0;
        return 0;
    }
    Pr[0][0] = 1;
    int answer;
    loop(layer,N-1) {
        // spreading from layer to layer+1
        loop(a,layer+2) {
            loop(b,layer+2) {
                answer = 0;
                if (arr[a][layer+1-a] == arr[N+b-layer-2][N-1-b]) {
                    vi As, Bs;
                    if (a>0) As.PB(a-1);
                    if (b>0) Bs.PB(b-1);
                    if (a<=layer) As.PB(a);
                    if (b<=layer) Bs.PB(b);
                    sloop(A,As) sloop(B,Bs) {
                        // if (arr[A][layer-A]==arr[N-1+B-layer][N-1-B]) {
                        answer += Pr[A][B];
                        answer %= MOD;
                        // }
                    }
                }
                Ne[a][b] = answer;
            }
        }
        loop(a,layer+2) {
            loop(b,layer+2) {
                // if (arr[a][layer+1-a] == arr[N+b-layer-2][N-1-b]) {
                Pr[a][b] = Ne[a][b];
                // }
            }
        }
        // swap(Pr,Ne);
    }
    answer = 0;
    loop(row,N) {
        answer += Ne[row][row];
        answer %= MOD;
    }
    cout << answer;
}