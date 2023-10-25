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

const string deCap(string wordRaw) {
    string fixedWord;
    sloop(newchar,wordRaw) {
        if (lower.find(newchar) != string::npos) {
            fixedWord += newchar;
        } else {
            fixedWord += lower[upper.find(newchar)];
        }
    }
    return fixedWord;
}

const bool isAnagram(string wordRaw1, string wordRaw2) {
    string word1 = deCap(wordRaw1);
    string word2 = deCap(wordRaw2);
    sort(word1.begin(),word1.end());
    sort(word2.begin(),word2.end());
    return (word1 == word2);
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string word;
    vector<string> words;
    vector<string> answers;
    while (true) {
        cin >> word;
        if (word == "#") break;
        words.PB(word);
    }
    loop(i,words.size()) {
        string word1 = words[i];
        bool condition = true;
        loop(j,words.size()) {
            if ((i != j) && (isAnagram(word1,words[j]))) {
                condition = false;
            }
        }
        if (condition) answers.PB(word1);
    }
    sort(answers.begin(),answers.end());
    sloop(word,answers) {
        cout << word << "\n";
    }
}