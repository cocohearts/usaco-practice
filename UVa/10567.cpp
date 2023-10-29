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

    string longS;
    int Q;
    cin >> longS >> Q;
    string map = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector<vi> indices(52,vi(0));
    int index;
    itloop(charIt,longS) {
        index = map.find(*charIt);
        indices[index].PB(charIt-longS.begin());
    }
    loop(i,Q) {
        string query;
        cin >> query;
        index = 0;
        int bot, mid, top;
        int charIndex;
        int first,last;
        bool matched = true;
        itloop(charIt,query) {
            charIndex = map.find(*charIt);
            if (*(indices[charIndex].end()-1) < index) {
                matched = false;
                break;
            }
            bot = 0;
            top = indices[charIndex].size();
            while (top>bot) {
                mid = (top+bot)/2;
                if (indices[charIndex][mid] < index) {
                    bot = mid+1;
                } else {
                    top = mid;
                }
            }
            index = indices[charIndex][bot]+1;
            if (charIt == query.begin()) {
                first = index-1;
            } 
            if (charIt == query.end()-1) {
                last = index-1;
            }
        }
        if (matched) {cout << "Matched " << first << " " << last << "\n";}
        else {cout << "Not matched\n";}
    }
}