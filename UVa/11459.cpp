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

    int cases;
    cin >> cases;
    loop (caseNum, cases) {
        int players, portals, rolls;
        cin >> players >> portals >> rolls;
        map<int,int> portal;
        int inpoint,endpoint;
        loop(i,portals) {
            cin >> inpoint >> endpoint;
            portal[inpoint] = endpoint;
        }
        vector<int> playerPoses(players,1);
        int playerTurn, roll, playerPos;
        loop(i,rolls) {
            playerTurn = i%players;
            cin >> roll;
            int playerPos = playerPoses[playerTurn] + roll;
            if (portal.find(playerPos)!=portal.end()) {
                playerPos = portal[playerPos];
            }
            playerPoses[playerTurn] = playerPos;
        }
        loop(player,players) {
        cout << "Position of player " << player+1 << " is " << playerPoses[player] << ".\n";
        }
    }
    cout << "\n";
}