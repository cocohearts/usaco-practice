#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int height, slide, fatiguePercent;
    float climb;
    while (true) {
        cin >> height >> climb >> slide >> fatiguePercent;
        if (height == 0) {
            break;
        }
        float fatigue = fatiguePercent / 100.0 * climb;
        int day = 1;
        float curHeight = 0.0;
        while (true) {
            curHeight += climb;
            if (curHeight > height) {
                cout << "success on day " << day << "\n";
                break;
            }
            curHeight -= slide;
            climb -= fatigue;
            if (climb < 0) {
                climb = 0;
            }

            if (curHeight < 0) {
                cout << "failure on day " << day << "\n";
                break;
            }

            day++;
        }
    }
}