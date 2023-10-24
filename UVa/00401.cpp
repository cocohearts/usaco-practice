#include <bits/stdc++.h>
#include <iostream>
#include <map>

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

    string line;
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    string mirrors  = "A000300HIL0JM0O0002TUVWXY51SE0Z0080";

    map<char,char> mirrorMap;
    loop(i,36) {
        mirrorMap[alphabet[i]] = mirrors[i];
    }
    
    while (cin >> line) {
        bool palindrome = true;
        bool mirrored = true;
        loop(i,line.size()) {
            if (line[i] != line[line.size()-i-1]) {
                palindrome = false;
            }
            if (line[i] != mirrorMap[line[line.size()-i-1]]) {
                mirrored = false;
            }
        }
        string response;
        if (!palindrome) {
            if (!mirrored) {
                response = "not a palindrome";
            } else {
                response = "a mirrored string";
            }
        } else if (!mirrored) {
            response = "a regular palindrome";
        } else {
            response = "a mirrored palindrome";
        }
        cout << line << " -- is " << response << ".\n\n";
    }
}