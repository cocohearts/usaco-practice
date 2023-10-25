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

int rate(char myChar) {
    int value;
    if (myChar - 'A'>26) {
        value = (myChar - 97)*2 + 1;
    } else {value = (myChar-65)*2;}
    return value;
}

struct cmp {
    bool operator()(const char char1,const char char2) {
        return rate(char1) < rate(char2);
    }
};


vector<string> permute(string word) {
    char prevChar = ':';
    vector<string> answers;
    if (word.size()==1) {
        answers.PB(word);
        return answers;
    }
    loop(charIndex,word.size()) {
        char newChar = word[charIndex];
        if (newChar != prevChar) {
            string newWord = word;
            newWord.erase(newWord.begin()+charIndex);
            vector<string> newAnswers = permute(newWord);
            sloop(cutWord,newAnswers) {
                answers.PB(newChar+cutWord);
            }
        }
        prevChar = newChar;
    }
    return answers;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        string word;
        cin >> word;
        sort(word.begin(),word.end(),cmp());
        sloop(permutation,permute(word)) {
            cout << permutation << "\n";
        }
    }
}