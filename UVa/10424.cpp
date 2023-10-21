#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define sloop(e,s) for(auto&& e : s)

map<char,int> letterMap;
map<char,int> digitMap;

string str1 = "abcdefghijklmnopqrstuvwxyz";
string str2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int digest(string myStr, map<char,int> myMap) {
    int sum = 0;
    sloop(myChar,myStr) {
        if (myMap.find(myChar) != myMap.end()) {
            sum += myMap[myChar];
        }
    }
    return sum;
}

int fulldigest(string myStr) {
    int firstN = digest(myStr,letterMap);
    while(true) {
        string newStr = to_string(firstN);
        if (newStr.size()==1) {
            break;
        }
        firstN = digest(newStr,digitMap);
    }
    return firstN;
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed;

    string n, m;

    loop(i,26) {
        letterMap[str1[i]]=i+1;
        letterMap[str2[i]]=i+1;
    }

    loop(i,9) {
        digitMap['0'+i]=i;
    }

    int intN,intM;

    while (true) {
        getline(cin,n);
        getline(cin,m);
        intN = fulldigest(n);
        intM = fulldigest(m);
        int mymin = min(intN,intM);
        int mymax = max(intN,intM);
        float percentage = (mymin * 100.0) / mymax;
        cout << setprecision(2) << percentage << " %";
        if (cin.eof()) {
            break;
        }
        cout << "\n";
    }
}