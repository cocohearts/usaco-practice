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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    iloop(a,1,2000) {
        iloop(b,a,2000-a) {
            iloop(c,b,2000-a-b) {
                if (a*b*c>1000000) {
                    if (1000000*(a+b+c)%(1000000-a*b*c)==0) {
                        int d = 1000000*(a+b+c)/(a*b*c-1000000);
                        if (2000 >= a+b+c+d && d >= c) {
                            printf("%.2f %.2f %.2f %.2f\n",a/100.0,b/100.0,c/100.0,d/100.0);
                        }
                    }
                }
            }
        }
    }
}