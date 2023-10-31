#include <bits/stdc++.h>
#include <iostream>
#include <set>

using namespace std;

typedef long long        ll;
typedef long              l;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000000000000L
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

    int N;
    cin >> N;
    vector<long> partials(1,0L);
    long partial=0;
    long newElem;
    loop(i,N) {
        cin >> newElem;
        partial += newElem;
        partials.PB(partial);
    }
    vector<vector<long>> on(N+1);
    vector<vector<long>> off(N+1);
    vector<pair<long, pair<int,int>>> subSeqs;
    loop(i,N) {
        iloop(j,i+1,N+1) {
            ii pairint = MP(i,j);
            subSeqs.PB(MP(partials[j]-partials[i],pairint));
        }
    }

    sort(subSeqs.begin(),subSeqs.end());
    long diff;
    vi endpoints;
    ii pair1,pair2;
    for(auto&& seqIt=subSeqs.begin(); seqIt!=subSeqs.end()-1; ++seqIt) {
        diff = (*(seqIt+1)).F - (*seqIt).F;
        pair1 = (*(seqIt)).S;
        pair2 = (*(seqIt+1)).S;
        endpoints = {pair1.F,pair1.S,pair2.F,pair2.S};
        sort(endpoints.begin(),endpoints.end());
        on[endpoints[0]].PB(diff);
        on[endpoints[2]].PB(diff);
        off[endpoints[1]].PB(diff);
        off[endpoints[3]].PB(diff);
    }
    multiset<long> minSet;

    loop(i,N) {
        sloop(onItem,on[i]) {
            minSet.insert(onItem);
        }
        sloop(offItem,off[i]) {
            auto hit = minSet.find(offItem);
            minSet.erase(hit);
        }
        cout << *minSet.begin() << "\n";
    }
}