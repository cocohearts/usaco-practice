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

int main() {
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int RFP=1; true; ++RFP) {
        int reqs, props;
        cin >> reqs >> props;
        cin.get();

        if (reqs == 0) {
            break;
        }

        if (RFP > 1) {
            cout << "\n";
        }

        cout << "RFP #" << RFP << "\n";

        string winner;
        int winningPrice = INF;
        int maxSatis = 0;
        vector<string> req_list;
        map<string,int> req_map;
        loop(i,reqs) {
            string req;
            // cin >> ws;
            // getline(cin,req);
            // cin.get();
            getline(cin,req);
            // cout << req << "\n";
            // cin >> ws;
            // req_list.push_back(req);
            // req_map[req] = i;
        }

        loop(propInd,props) {
            string newProp;
            float price;
            int satis;
            // cin >> ws;
            // cin.get();
            getline(cin,newProp);
            // cout << newProp << "\n";
            // cin >> ws;
            cin >> price >> satis;
            if (maxSatis<satis || (maxSatis==satis && price < winningPrice)) {
                winner = newProp;
                winningPrice = price;
                maxSatis = satis;
            }
            cin.get();
            string randReq;
            loop(i,satis) {
                // cin >> ws;
                // cin.get();
                getline(cin,randReq);
                // cout << randReq << "\n";
                // cin >> ws;
            }
        }
        cout << winner << "\n";
    }
}