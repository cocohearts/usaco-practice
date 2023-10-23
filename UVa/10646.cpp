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

vector<char> ranks = {
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'T',
    'J',
    'Q',
    'K',
    'A'
};

vector<char> suits = {
    'S',
    'H',
    'D',
    'C'
};

map<char,int> rankMap;
map<char,int> suitMap;

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // loop(i,13) {
    //     if (i>=8) {
    //         rankMap[ranks[i]] = 10;
    //     } else {rankMap[ranks[i]] = i+2;}
    // }
    // loop(i,4) {
    //     suitMap[suits[i]] = i;
    // }

    int cases;
    cin >> cases;
    loop (i,cases) {
        cout << "Case " << i+1 << ": ";
        vector<string> stack;
        string card;
        loop(i,52) {
            cin >> card;
            stack.PB(card);
        }
        // int Y=0;
        // int pile_top = 25;
        // loop(i,3) {
        //     int X = rankMap[stack[pile_top][0]];
        //     pile_top += 11-X;
        //     Y += X;
        // }
        // int bottom = 52-pile_top;
        string answer;
        // if (Y <= bottom) {
        //     answer = stack[52-Y];
        // } else {
        //     answer = stack[25-(Y-bottom)];
        // }
        answer = stack[32];
        cout << answer << "\n";
    }
}