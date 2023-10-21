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

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string bitstring;
    int caseNum = 0;
    while (cin >> bitstring) {
        ++caseNum;
        cout << "Case " << caseNum << ":\n";

        if (!bitstring.size()) {
            break;
        }
        vi changes;
        changes.push_back(0);
        char curchar=bitstring[0];
        char mychar;
        loop(i,bitstring.size()) {
            mychar = bitstring[i];
            if (mychar != curchar) {
                curchar = mychar;
                changes.push_back(i);
            }
        }
        int queries;
        cin >> queries;
        int i,j,myMin,myMax;
        loop(qNum,queries) {
            cin >> i >> j;
            myMin = min(i,j);
            myMax = max(i,j);

            loop(cInd,changes.size()) {
                if (cInd < changes.size()-1) {
                    if (changes[cInd+1] > myMin) {
                        if (myMax >= changes[cInd+1]) {
                            cout << "No\n";
                            break;
                        }
                        cout << "Yes\n";
                        break;
                    }
                }
                if (cInd == changes.size()-1) {
                    cout << "Yes\n";
                    break;
                }
            }
        }
    }
}