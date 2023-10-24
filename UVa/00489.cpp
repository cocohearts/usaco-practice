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

string letters = "abcdefghijklmnopqrstuvwxyz";
map<char,int> indexMap;

int main() {
    // freopen("input","r",stdin);
    loop(i,26) {
        indexMap[letters[i]] = i;
    }
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNum;
    string word;
    string letters;
    while (true) {
        cin >> caseNum;
        if (caseNum < 0) {
            break;
        }
        cout << "Round " << caseNum << "\n";
        cin >> word;
        cin >> letters;
        vector<bool> found(26,false);
        vector<bool> guessed(26,false);
        int guessedCount = 0;
        int lettersRemain = 0;
        sloop(letter,word) {
            if (!found[indexMap[letter]]) {
                ++lettersRemain;
                found[indexMap[letter]] = true;
            }
        }
        sloop(letter,letters) {
            if (!guessed[indexMap[letter]]) {
                guessed[indexMap[letter]] = true;
                if (found[indexMap[letter]]) {
                    --lettersRemain;
                } else {
                    ++guessedCount;
                }
            }
            if (guessedCount==7) {
                cout << "You lose.\n";
                break;
            }
            if (!lettersRemain) {
                cout << "You win.\n";
                break;
            }
        }
        if (lettersRemain && guessedCount<7) {
            cout << "You chickened out.\n";
        }

    }
}