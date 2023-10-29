#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
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

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int K;
        cin >> K;
        vector<string> grid1,grid2;
        string row;
        loop(i,6) {
            cin >> row;
            grid1.PB(row);
        }
        loop(i,6) {
            cin >> row;
            grid2.PB(row);
        }
        vector<string> possibilities;
        vi possNum;
        int totPoss=1;
        loop(i,5) {
            string possibility,col1,col2;
            loop(j,6) {
                col1 += grid1[j][i];
                col2 += grid2[j][i];
            }
            loop(j,26) {
                char newChar = 'A'+j;
                if (col1.find(newChar)!=string::npos && col2.find(newChar)!=string::npos) {
                    possibility += newChar;
                }
            }
            possibilities.PB(possibility);
            possNum.PB(possibility.size());
            totPoss *= possibility.size();
        }
        --K;
        if (K >= totPoss) {
            cout << "NO\n";
        } else {
            string answer;
            loop(i,5) {
                totPoss /= possNum[i];
                answer += possibilities[i][(K/totPoss)%possNum[i]];
            }
            cout << answer << "\n";
        }
    }
}