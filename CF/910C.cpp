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

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int n,m,k;
        cin >> n >> m >> k;
        if (abs(n+m-k)%2==1) {
            cout << "NO\n";
            continue;
        } if (k < n+m-2) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        loop(i,n) {
            loop(j,m-1) {
                if (j%2) {
                    cout << 'R';
                } else {
                    cout << 'B';
                }
                if (j<m-2) {
                    cout << ' ';
                }
            }
            cout << "\n";
        }
        // if (abs(n+m-k)%4==2) {
        loop(i,n-1) {
            loop(j,m) {
                if (j==m-1) {
                    if ((i+m)%2) {
                        cout << 'B';
                    } else {
                        cout << 'R';
                    }
                } else {
                    cout << 'R';
                }
                if (j<m-1) {
                    cout << ' ';
                }
            }
            cout << "\n";
        }
        // } else {
        //     loop(i,n-1) {
        //         loop(j,m) {
        //             if (j==m-1) {
        //                 if ((i+n)%2) {
        //                     cout << 'R';
        //                 } else {
        //                     cout << 'B';
        //                 }
        //             } else {
        //                 cout << 'R';
        //             }
        //             if (j<m-1) {
        //                 cout << ' ';
        //             }
        //         }
        //         cout << "\n";
        //     }
        // }
    }
}