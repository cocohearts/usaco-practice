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

    int n, m, c;
    vector<bool> on;
    vector<int> consum;
    int new_consum, new_toggle;
    for (int seq = 1; true; ++seq) {
        bool known = false;
        cin >> n >> m >> c;
        if (n == 0) {
            break;
        }
        if (seq > 1) {
            cout << "\n";
        }
        cout << "Sequence " << seq << "\n";
        loop(i,n) {
            cin >> new_consum;
            consum.push_back(new_consum);
        }
        int power = 0;
        int max_consum = 0;

        on.resize(n);
        on.clear();

        loop(i,m) {
            cin >> new_toggle;
            --new_toggle;
            on[new_toggle] = !on[new_toggle];
            if (on[new_toggle]) {
                power += consum[new_toggle];
                max_consum = max(max_consum,power);
                if (power > c) {
                    if (!known) {
                        cout << "Fuse was blown.\n";
                        known = true;
                    }
                }
            } else {
                power -= consum[new_toggle];
            }

            if (i==m-1 && !known) {
                cout << "Fuse was not blown.\nMaximal power consumption was " << max_consum << " amperes.\n";
                known = true;
            }

        consum.resize(0);
        }
    }
    cout << "\n";
}