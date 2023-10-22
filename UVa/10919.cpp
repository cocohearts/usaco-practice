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

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k,m;
    while (true) {
        cin >> k >> m;
        if (!k) {
            break;
        }
        vi courses;
        int course;
        loop(i,k) {
            cin >> course;
            courses.push_back(course);
        }
        string works = "yes";
        loop(i,m) {
            int catNum, catReq;
            cin >> catNum >> catReq;
            int catCourse;
            loop(j,catNum) {
                cin >> catCourse;
                if (find(courses.begin(),courses.end(),catCourse)!=courses.end()) {
                    --catReq;
                }
            }
            if (catReq > 0) {
                works = "no";
            }
        }
        cout << works << "\n";
    }
}