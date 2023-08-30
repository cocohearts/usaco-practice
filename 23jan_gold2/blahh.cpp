#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n;
  cin >> t >> n;
  auto cyc_right = [&n](int x) -> int {
    x <<= 1;
    if (x & (1 << n)) {
      x ^= (1 << n) ^ 1;
    }
    return x;
  };
  auto str_to_bin = [&n](string s) -> int {
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (s[i] == '1') {
        res ^= (1 << i);
      }
    }
    return res;
  };
  vector<int> rep(1 << n, -1);
  for (int i = 0; i < 1 << n; ++i) {
    if (rep[i] == -1) {
      int j = i;
      while (rep[j] == -1) {
        rep[j] = i;
        j = cyc_right(j);
      }
    }
  }
  vector<vector<bool>> can(3*n + 1, vector<bool>(1 << n));
  can[0][rep[0]] = true;
  int cur_pad = 0;
  for (int i = 1; i <= 3*n; ++i) {
    cur_pad ^= 1<<((i-1)%n);
    for (int mask = 0; mask < 1 << n; ++mask) {
      if (can[i - 1][rep[mask]]) {
        can[i][rep[cur_pad ^ mask]] = true;
      }
    }
  }
  while (t--) {
    string x, y;
    cin >> x >> y;
    int pad = str_to_bin(y);
    int fin = str_to_bin(x);
    int cur = 0;
    for (int i = 0; i <= 3*n; ++i) {
      if (can[i][rep[cur ^ fin]]) {
        cout << i << '\n';
        break;
      }
      cur ^= pad;
      pad = cyc_right(pad);
    }
  }
  return 0;
}