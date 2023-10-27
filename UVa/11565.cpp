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
    // 13:56
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    int A,B,C,criteria;
    loop(caseNum, numCases) {
        bool solved = false;
        cin >> A >> B >> C;
        criteria = (int)sqrt(C);
        iloop(x,-1*criteria,criteria+1) {
            if (B%x==0) {
                criteria = (int)sqrt((C-x*x)/2);
                iloop(y,-1*criteria,criteria+1) {
                    if (B/x % y==0 && x!=y) {
                        int z = A-x-y;
                        if (x*y*z==B && x*x+y*y+z*z==C && x!=z && y!=z) {
                            solved = true;
                            cout << x << " " << y << " " << z << "\n";
                            break;
                        }
                    }
                }
                if (solved) break;
            }
        }
        if (!solved) cout << "No solution.\n";
    }
}