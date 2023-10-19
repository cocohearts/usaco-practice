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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<string,int> name_map;
    bool passed_one = false;
    int nameNum = 0;
    while (cin >> nameNum) {
        if (nameNum == 0) {
            break;
        }

        if (passed_one) {
            cout << "\n";
        } else {
            passed_one = true;
        }

        string name;
        vector<string> names(nameNum);
        loop(i,nameNum) {
            cin >> name;
            name_map[name] = i;
            names[i] = name;
        }
        vi wealth(nameNum,0);
        int money, recipients;
        loop(i,nameNum) {
            cin >> name >> money >> recipients;
            if (!recipients) {
                continue;
            }
            int index = name_map[name];
            int gifts = money / recipients;
            wealth[index] -= gifts * recipients;
            string recipientName;
            loop(j,recipients){
                cin >> recipientName;
                wealth[name_map[recipientName]] += gifts;
            }
        }
        loop(i,nameNum) {
            cout << names[i] << " " << wealth[i] << "\n";
        }
    }
}