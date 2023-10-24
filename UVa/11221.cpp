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

string alph = "abcdefghijklmnopqrstuvwxyz";

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    cin.get();
    loop(caseNum,numCases) {
        cout << "Case #" << caseNum+1 << ":\n";
        string newline;
        getline(cin,newline);
        string letters;
        bool works = true;
        loop(i,newline.size()) {
            char newChar = newline[i];
            if (alph.find(newChar) != string::npos) {
                letters += newChar;
            }
        }
        float sqrtft = sqrt(letters.size());
        int K = (int) sqrtft;
        if (K*K == letters.size()) {
            loop(loc,K*K) {
                int transp = K*(loc%K) + (loc/K);
                if ((letters[loc]!=letters[transp]) || (letters[loc]!=letters[K*K-loc-1])) {
                    works = false;
                    break;
                }
            }
        } else {works = false;}
        string response = works ? to_string(K) : "No magic :(";
        cout << response << "\n";
    }
}