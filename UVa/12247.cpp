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

bool die(vi princess,vi prince) {
    sort(princess.begin(),princess.end());
    sort(prince.begin(),prince.end());
    int wins = 0;
    if (princess[2] > prince[1]) ++wins;
    if (princess[1] > prince[0]) ++wins;
    return (wins == 2);
}

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        vi cards;
        vi princess;
        vi prince;
        int card;
        loop(i,5) {
            cin >> card;
            cards.PB(card);
            if (i<3) {
                princess.PB(card);
            } else {prince.PB(card);}
        }
        if (!card) {
            break;
        }
        // check for instaloss
        sort(prince.begin(),prince.end());
        sort(princess.begin(),princess.end());
        sort(cards.begin(),cards.end());
        int answer = -1;
        for (int newCard=1; newCard<53; ++newCard) {
            if (find(cards.begin(),cards.end(),newCard) == cards.end()) {
                prince.PB(newCard);
                if (!die(princess,prince)) {
                    answer = newCard;
                    break;
                } else {
                    prince.pop_back();
                }
            }
        }
        cout << answer << "\n";
    }
}