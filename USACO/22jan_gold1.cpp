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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P = 1000000007;

    int N;
    cin >> N;
    int level, levels[N];
    loop(i,N) {
        cin >> level;
        ++level;
        levels[i] = level;
    }
    int sols[1000][100][1000];
    loop(base,1000) {
        loop(curIndex,N) {
            if (!curIndex) {
                loop(val,1000) {
                    if (val!=base) {
                        sols[base][curIndex][val] = 0;
                    } else {
                        sols[base][curIndex][val] = 1;
                    }
                }
            } else {
                int prefSum = 0;
                for (int val = levels[curIndex-1]; val >= base; --val) {
                    prefSum += sols[base][curIndex-1][levels[curIndex-1]-val+base];
                    prefSum %= P;
                    if (val < levels[curIndex]) {
                        sols[base][curIndex][val] = prefSum;
                    }
                }
            }
        }
    }
    int answer = 0;
    loop(val,1000) {
        answer += sols[0][N-1][val];
        answer %= P;
    } 
    if (N%2) {
        iloop(base,1,1000) {
            loop(val,1000) {
                answer += sols[base][N-1][val];
                answer %= P;
            }
        }
    }
    cout << answer;
}