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
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    loop(i,13) {
        rankMap[ranks[i]] = i;
    }
    loop(i,4) {
        suitMap[suits[i]] = i;
    }

    while (true) {
        vector<vi> hand{{},{},{},{}};
        
        string card;
        int rank,suit;
        loop(i,13) {
            cin >> card;
            rank = rankMap[card[0]];
            suit = suitMap[card[1]];
            if (suit < 4) {
                hand[suit].push_back(rank);
            }
        }
        if (!card.size()) {
            break;
        }
        if (card=="4C") {
            int k;
        }
        int points = 0;
        int bonus567 = 0;
        int maxSize = 0;
        int maxSuit;
        int stoppedCount = 0;
        loop(suitIndex, 4) {
            bool stopped = false;
            vi suit = hand[suitIndex];
            sloop(rank,suit) {
                if (rank > 8) {
                    points += rank-8;
                    if (rank + suit.size() <= 12) {
                        --points;
                    }
                }
                if (rank >= 10) {
                    if (rank + suit.size() >= 13) {
                        stopped = true;
                    }
                }
            }
            if (suit.size()==2) {
                ++bonus567;
            }
            if (suit.size()<=1) {
                bonus567 += 2;
            }
            if (suit.size() > maxSize) {
                maxSize = suit.size();
                maxSuit = suitIndex;
            }
            if (stopped) {++stoppedCount;}
        }
        if (points+bonus567 < 14) {
            cout << "PASS\n";
        } else if (points>=16 && stoppedCount==4) {
            cout << "BID NO-TRUMP\n";
        } else {
            cout << "BID " << suits[maxSuit] << "\n";
        }
    }
        
}