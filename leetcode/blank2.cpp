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

    vi nums{ 2,3 };

    sort(nums.begin(),nums.end());
    int N = nums.size();
    int maxLen = 0;
    int maxElem = nums[N-1];
    while (maxElem) {
        ++maxLen;
        maxElem /= 2;
    }
    int pref, realPref=0;
    int maxes[1<<maxLen], mins[1<<maxLen];
    for (int len=0; len<maxLen; ++len) {
        realPref *= 2;
        pref = realPref+1;
        // int maxes[1<<(len+1)], mins[1<<(len+1)];
        for (int i=0; i<1<<(len+1); ++i) {
            maxes[i] = -100000000;
            mins[i]  = 100000000;
        }
        for (int index=0; index<N; ++index) {
            int curPref = nums[index] >> (maxLen-len-1);
            maxes[curPref] = max(maxes[curPref],nums[index]);
            mins[curPref] = min(mins[curPref],nums[index]);
        }
        for (int potPref=0; potPref < 1<<(len); ++potPref) {
            int opp = pref ^ potPref;
            if (opp >= potPref) {
                if ((mins[opp] <= 2*maxes[potPref])) {
                    realPref = pref;
                    break;
                }
            }
        }
    }
    cout << realPref;
}