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

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int answer=0;
        int days;
        cin >> days;
        int sales[days];
        int sale;
        loop(day,days) {
            cin >> sale;
            sales[day] = sale;
        }
        loop(day1,days) {
            for (int day2 = day1+1; day2<days; ++day2) {
                if (sales[day1] <= sales[day2]) ++answer;
            }
        }
        printf("%u\n",answer);
    }
}