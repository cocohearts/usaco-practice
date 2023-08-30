#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("lights.in","r",stdin);
    int T, N;
    cin >> T >> N;
    int SIZE = (1 << N);
    int len = 3*N+1;

    auto cyc_one_shift = [&N](int x) -> int {
        x <<= 1;
        if (x & (1 << N)) {
            x ^= (1 << N) ^ 1;
        }
        return x;
    };
    auto str_to_bin = [&N](string s) -> int {
        int res = 0;
        for (int i = 0; i < N; ++i) {
            if (s[i] == '1') {
                res ^= (1 << i);
            }
        }
        return res;
    };

    vector< int > rep(SIZE, -1);
    for (int i=0; i<SIZE; ++i) {
        if (rep[i]==-1) {
            rep[i] = i;
            int j = cyc_one_shift(i);
            while (j!= i) {
                rep[j] = i;
                j = cyc_one_shift(j);
            }
        }
    }

    vector< vector<bool> > possible(len, vector<bool> (SIZE));
    possible[0][rep[0]] = true;
    int mystring = 0;
    for (int turns=0; turns<len-1; ++turns) {
        mystring ^= 1<<(turns%N);
        for (int starting=0; starting<SIZE; ++starting) {
            if (possible[turns][rep[starting]]) {
                possible[turns+1][rep[starting ^ mystring]] = true;
            }
        }
    }
    // for (int i=0; i<SIZE; ++i) {
    //     for (int j=0; j<2*N; ++j) {
    //         cout << possible[j][rep[i]] << " ";
    //     }
    //     cout << endl;
    // }
    while (T--) {
        string light_str, switch_str;
        int lights, switches;
        cin >> light_str >> switch_str;
        // reverse(switch_str.begin(),switch_str.end());
        // reverse(light_str.begin(),light_str.end());
        lights = str_to_bin(light_str);
        switches = str_to_bin(switch_str);
        int steps = 0;
        int currentlights = 0;
        while (! possible[steps][rep[currentlights ^ lights]]) {
            ++steps;
            currentlights ^= switches;
            switches = cyc_one_shift(switches);
        }
        cout << steps << endl;
    }
    return 0;
}