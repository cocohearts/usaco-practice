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

bool check(vector<string> times) {
    int len = times.size();
    for (int i=0; i<len-2; i++) {
        string time1 = times[i];
        string time2 = times[i+2];
        if (time1[1]==time2[1]) {
            return true;
        }
        if ((time2[1]-time1[1])==1) {
            int min1 = stoi(time1.substr(2,2));
            int min2 = stoi(time2.substr(2,2));
            if (min2 < min1) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<string>> access_times = {{"a","0549"},{"b","0457"},{"a","0532"},{"a","0621"},{"b","0540"}};
    // {{"d","0002"},{"c","0808"},{"c","0829"},{"e","0215"},{"d","1508"},{"d","1444"},{"d","1410"},{"c","0809"}}{{"cd","1025"},{"ab","1025"},{"cd","1046"},{"cd","1055"},{"ab","1124"},{"ab","1120"}};
    vector<string> answer;
    vector<string> seen;
    for (int i=0; i<access_times.size(); ++i) {
        string employee = access_times[i][0];
        if (find(seen.begin(),seen.end(),employee) == seen.end()) {
            seen.push_back(employee);
            vector<string> times;
            for (int j=0; j<access_times.size(); ++j) {
                if (access_times[j][0]==employee) {
                    times.push_back(access_times[j][1]);
                }
            }
            sort(times.begin(),times.end());
            if (check(times)) {
                answer.push_back(employee);
            }
        }
    }
    // cout << answer;
    return answer;
}