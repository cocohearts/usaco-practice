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

// pair max, size
ii DP[248][248];
// pair left, right, 
pair<bool,bool> AD[248][248];

int main() {
    // freopen("input","r",stdin);
    freopen("248.in","r",stdin);
    freopen("248.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    int arr[N];
    loop(i,N) {
        cin >> arr[i];
    }
    loop(iSi,N) {
        loop(iSt,N-iSi) {
            if (!iSi) {
                DP[iSt][iSt] = MP(arr[iSt],1);
                AD[iSt][iSt] = MP(true,true);
                continue;
            }
            int iEn = iSt+iSi;
            bool left = false, right = false;
            int ans = 0, size = INT_MAX;
            iloop(iMi,iSt,iEn) {
                int max1 = DP[iSt][iMi].F;
                int max2 = DP[iMi+1][iEn].F;
                int cur = max(max1,max2);
                int siz = DP[iSt][iMi].S + DP[iMi+1][iEn].S;
                bool cLeft = AD[iSt][iMi].F;
                bool cRight = AD[iMi+1][iEn].S;
                if (AD[iSt][iMi].S && AD[iMi+1][iEn].F && max1==max2) {
                    ++cur;
                    --siz;
                    if (DP[iSt][iMi].S>1) {
                        cLeft = false;
                    }
                    if (DP[iMi+1][iEn].S>1) {
                        cRight = false;
                    }
                } else {
                    if (max1>max2) {
                        cRight = false;
                    }
                    if (max2>max1) {
                        cLeft = false;
                    }
                }
                if (cur > ans) {
                    ans = cur;
                    left = cLeft; right = cRight;
                    size = siz;
                } else if (cur == ans) {
                    left |= cLeft; right |= cRight;
                    size = min(size,siz);
                    // size = siz;
                }
            }
            DP[iSt][iEn] = MP(ans,size);
            AD[iSt][iEn] = MP(left,right);
        }
    }
    cout << DP[0][N-1].F;
}