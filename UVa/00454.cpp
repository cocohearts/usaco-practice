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
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    string newline;
    cin.get(); getline(cin,newline);
    loop(caseNum,numCases) {
        vector<string> phrases;
        map<string,vector<string>> mapToWord;
        while (true) {
            getline(cin,newline);
            if (newline.size()<=1) {
                break;
            }
            phrases.PB(newline);
        }
        if (caseNum) {
            cout << "\n";
        }
        string newword;
        sloop(phrase,phrases) {
            newword = phrase;
            newword.erase(remove_if(newword.begin(),newword.end(),::isspace),newword.end());
            sort(newword.begin(),newword.end());
            mapToWord[newword].PB(phrase);
        }
        vector<string> equalities;
        for (auto&& it=mapToWord.begin(); it!=mapToWord.end(); ++it) {
            vector<string> phraseList = it->S;
            sort(phraseList.begin(),phraseList.end());
            loop(i,phraseList.size()) {
                loop(j,phraseList.size()-i-1) {
                    equalities.PB(phraseList[i]+" = "+phraseList[i+j+1]+"\n");
                }
            }
            sort(equalities.begin(),equalities.end());
        }
        sloop(equality,equalities) {
            cout << equality;
        }
    }

}