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

vi bestSet;
vi Set;
int bestCover;
int b,p;

void iterate(vii shared,vi individ){
    if (Set.size()==b) {
        int s = 0;
        sloop(tow,Set) s+=1<<tow;
        int cover = 0;
        loop(i,p) {
            if (1<<i & s) {
                cover += individ[i];
            }
        }
        sloop(sharedPair,shared) {
            if (sharedPair.F & s) {
                cover += sharedPair.S;
            }
        }
        if (cover > bestCover) {
            bestSet = Set;
            bestCover = cover;
        }
    } else {
        int start = (Set.size()>0) ? Set[Set.size()-1]+1 : 0;
        iloop(nextTow,start,p) {
            Set.PB(nextTow);
            iterate(shared,individ);
            Set.pop_back();
        }
    }
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int caseNum=1; true; ++caseNum) {
        cin >> p >> b;
        if (p+b==0) break;
        // if (caseNum > 1) {
        //     cout << "\n";
        // }
        cout << "Case Number  " << caseNum << "\n";
        vi individ(p);
        int place;
        loop(i,p) {
            cin >> place;
            individ[i] = place;
        }
        cin >> place;
        vii shared(place);
        int t, tow, pop;
        loop(i,place) {
            cin >> t;
            int bit = 0;
            loop(i,t) {
                cin >> tow;
                --tow;
                bit += 1<<tow;
            }
            cin >> pop;
            shared[i] = MP(bit,pop);
        }
        loop(i,p) {
            sloop(sharedPair,shared) {
                if (1<<i & sharedPair.F) {
                    individ[i]-=sharedPair.S;
                }
            }
        }
        bestCover = 0;
        iterate(shared,individ);
        cout << "Number of Customers: " << bestCover << "\n";
        cout << "Locations recommended:";
        sloop (tow, bestSet) {
            cout << " " << tow+1;
        }
        cout << "\n";
        cout << "\n";
    }
}