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

string lower = "abcdefghijklmnopqrstuvwxyz";
string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string newline;
    while (true) {
        getline(cin,newline);
        if (newline=="DONE") break;
        string letters = "";
        loop(i,newline.size()) {
            char newChar = newline[i];
            if (lower.find(newChar)!=string::npos) {
                letters.PB(newChar);
            } else if (upper.find(newChar)!=string::npos) {
                letters.PB(lower[upper.find(newChar)]);
            }
        }
        bool live = true;
        int letterSize = letters.size();
        loop(i,letters.size()) {
            if (letters[i]!=letters[letterSize-1-i]) {
                live = false;
            }
        }
        if (live) {cout << "You won't be eaten!\n";}
        else {cout <<  "Uh oh..\n";}
    }
}