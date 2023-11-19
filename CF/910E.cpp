#include <bits/stdc++.h>
#include <iostream>
#include <list>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define MOD 1000000007
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
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

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        int n,m;
        string s,t;
        cin >> n >> m;
        cin >> s >> t;
        list<int> s_arr;
        int t_arr[m];
        loop(i,n) {
            s_arr.emplace_back(s[i]-'a');
        }
        loop(i,m) {
            t_arr[i] = t[i]-'a';
        }
        // int s_ind = 0;
        int t_ind = 0;
        int counts[26];
        bool broke = false;
        loop(i,26) {
            counts[i] = 0;
        }
        int total = 0;
        while (t_ind<m) {
            // find increasing seq in s
            // ++counts[t_arr[t_ind]];
            // ++total;
            while (t_ind<m) {
                ++counts[t_arr[t_ind]];
                ++total;
                if (t_ind==m-1) {
                    ++t_ind;
                    break;
                } else if (t_arr[t_ind+1]<t_arr[t_ind]) {
                    ++t_ind;
                    break;
                } 
                ++t_ind;
            }
            // track max index remaining in current seg
            // if you are *in front* of that you must be removed
            // every time s_ind starts from 0, modify s
            int max_index=25;
            vi deleted;
            auto&& s_it = s_arr.begin();
            while (s_it != s_arr.end()) {
                if (!total) {
                    // found all in seg
                    break;
                }
                while (!counts[max_index]) --max_index;
                if (counts[*s_it]) {
                    --counts[*s_it];
                    --total;
                    s_it = s_arr.erase(s_it);
                } else if (*s_it < max_index) {
                    s_it = s_arr.erase(s_it);
                } else {
                    ++s_it;
                }
            }
            if (total>0) {
                cout << "NO\n";
                broke = true;
                break;
            }
            // while (total>0) {
            //     if (s_ind >= n) {
            //         cout << "NO\n";
            //         broke = true;
            //         break;
            //     }
            //     if (counts[s_arr[s_ind]]) {
            //         --counts[s_arr[s_ind]];
            //         --total;
            //     }
            //     ++s_ind;
            // }
            // if (broke) {
            //     break;
            // }
        }
        if (!broke) {
            cout << "YES\n";
        }
    }
}