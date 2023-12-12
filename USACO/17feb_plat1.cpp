#include "bits/stdc++.h"
using namespace std;

using ll = long long;
using ld = long double;
using db = double;
using str = string;

using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vl = vector<ll>;
using vd = vector<db>;
using vs = vector<str>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;

#define mp make_pair
#define f first
#define s second

// const int MOD = 1e9 + 7;
// const int MX = 2e5 + 5;
// const int INF = 1e9;
// const ll INF = 1e18;  // not too close to LLONG_MAX
// const ld PI = acos((ld)-1);
// const int dx[4] = {1, 0, -1, 0},
//           dy[4] = {0, 1, 0, -1};  // for every grid problem!!

#define sz(x) int(x.size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pb push_back
#define eb emplace_back
#define pf push_front

#define lb lower_bound
#define ub upper_bound

#define endl "\n"

#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define trav(a, x) for (auto &a : x)

// template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

constexpr int pct(int x) { return (int)__builtin_popcount(x); }
constexpr int bits(int x) {
	return x == 0 ? 0 : 31 - (int)__builtin_clz(x);
}
 
template <typename T, typename... U>
void dbgh(const T& t, const U&... u) {
    cerr << t;
    ((cerr << " | " << u), ...);
    cerr << endl;
}
 
void setPrec() { cout << fixed << setprecision(15); }
void unsyncIO() { cin.tie(0)->sync_with_stdio(0); }

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	unsyncIO();
	setPrec();
	cin.exceptions(cin.failbit);

	if (sz(s)) setIn(s + ".in"), setOut(s + ".out");
}

#ifdef LOCAL
	const int L = 100;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 100000;
	#define dbg(...)
#endif

int arrs[2][L];
int deltas[L];
int rev_arr1[L];

void solve() {
	int N; cin >> N;
	F0R(i,N) {cin >> arrs[0][i]; --arrs[0][i];}
	F0R(i,N) {cin >> arrs[1][i]; --arrs[1][i];}

	ll ret = 1e18;
	Tree<int> ordered_set;

	F0R(ind,2) {
		auto arr1 = arrs[ind], arr2 = arrs[1-ind];
		F0R(i,N) {
			deltas[arr2[i]] = N-1-2*i;
			rev_arr1[arr1[i]] = i;
		}

		ll crossing = 0;
		ordered_set.clear();
		F0R(i,N) {
			int arr1ind = rev_arr1[arr2[i]];
			ordered_set.insert(arr1ind);
			crossing += arr1ind - ordered_set.order_of_key(arr1ind);
		}
		ret = min(ret,crossing);
		F0R(i,N) {
			crossing += deltas[arr1[i]];
			ret = min(ret,crossing);
		}
	}
	cout << ret;
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("mincross");
	#endif

	solve();
}