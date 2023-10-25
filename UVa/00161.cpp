#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>

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
    freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        vi cycles;
        int cycleLen;
        while (true) {
            cin >> cycleLen;
            if (!cycleLen) {
                break;
            }
            cycles.PB(cycleLen);
        }
        if (cycles.size()==0) {
            break;
        }
        int time = *(min_element(cycles.begin(),cycles.end()))-5;
        while (time <= 18000) {
            bool works = true;
            sloop(cycle,cycles) {
                if (time % (2*cycle) >= cycle-5) {
                    works = false;
                }
            }
            if (works) break;
            ++time;
        }
        if (time<=18000) {
            int secs = time%60;
            int mins = (time%3600)/60;
            int hours = time/3600;
            cout << setfill('0') << setw(2) << hours << ":" << setfill('0') << setw(2) << mins << ":" << setfill('0') << setw(2) << secs << "\n";
        } else {
            cout << "Signals fail to synchronise in 5 hours\n";
        }
    }
}