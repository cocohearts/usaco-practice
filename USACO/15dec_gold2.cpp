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

int first[5000000], second[5000000];

int main() {
    // freopen("input","r",stdin);
    freopen("feast.in","r",stdin);
    freopen("feast.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T,A,B;
    cin >> T >> A >> B;
    ++T;
    first[0] = second[0] = true;
    bool works;
    iloop(i,1,T) {
        works = false;
        if (i>=A) {
            if (first[i-A]) works = true;
        }
        if (i>=B) {
            if (first[i-B]) works = true;
        }
        first[i] = works;
    }
    loop(i,T/2) {
        if (first[2*i] || first[2*i+1]) {second[i]=true;}
        else {second[i]=false;}
    }
    loop(i,T) {
        works = false;
        if (i>=A) {
            if (second[i-A]) works = true;
        }
        if (i>=B) {
            if (second[i-B]) works = true;
        }
        second[i] |= works;
    }
    for (int i=T-1; ; --i) {
        if (second[i]) {
            cout << i;
            return 0;
        }
    }

}