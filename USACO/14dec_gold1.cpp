#include <bits/stdc++.h>
#include <iostream>

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

int DP[1<<20];
int We[1<<20];
int He[1<<20];
int Hs[20],Ws[20],Ss[20];

int BM=0,Wsum=0,Hsum=0,step=0;
int N,H;
void compWeights() {
    if (step==N) {
        We[BM] = Wsum;
        He[BM] = Hsum;
    } else {
        ++step;
        compWeights();
        --step;
        BM += 1<<step;
        Wsum += Ws[step];
        Hsum += Hs[step];
        ++step;
        compWeights();
        --step;
        BM -= 1<<step;
        Wsum -= Ws[step];
        Hsum -= Hs[step];
    }
}

int main() {
    freopen("guard.in","r",stdin);
    freopen("guard.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> H;
    loop(i,N) {
        cin >> Hs[i] >> Ws[i] >> Ss[i];
    }
    int B = 1<<N;
    compWeights();

    int answer=-1;
    loop(bm, B) {
        int best=-1;
        if (!bm) best=INT_MAX;
        loop(ind,N) {
            if (bm & 1<<ind) {
                best = max(best,min(Ss[ind]-We[bm^1<<ind],DP[bm^1<<ind]));
            }
        }
        DP[bm] = best;
        if (He[bm]>=H) {
            answer = max(answer,best);
        }
    }
    if (answer<0) {
        cout << "Mark is too tall";
    } else cout << answer;
}