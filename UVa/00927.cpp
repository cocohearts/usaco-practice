#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
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
        int polySize,d;
        long long k;
        cin >> polySize;
        int polyCoeffs[polySize+1];
        int polyCoeff;

        loop(i,polySize+1) {
            cin >> polyCoeff;
            polyCoeffs[i] = polyCoeff;
        }
        cin >> d >> k;
        long long frac = (k-1)/d+1;
        int mySqrt = sqrt(2*frac);
        if (mySqrt*(mySqrt+1)/2 < frac) {
            ++mySqrt;
        }
        // answer is a_{mySqrt}
        long long answer = 0;
        loop(i,polySize+1) {
            answer += polyCoeffs[i] * pow(mySqrt,i);
        }
        cout << answer << "\n";
    }
}