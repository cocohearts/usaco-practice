#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

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

template <class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

constexpr int pct(int x) { return (int)__builtin_popcount(x); }
constexpr int bits(int x) {
	return x == 0 ? 0 : 31 - (int)__builtin_clz(x);
}

template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
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
	const int L = 600000;
	#define dbg(...)
#endif

ll starting[L];
pl queries[L];
ll anses[L];
pl states[L];
Tree<ll> myTree;

void solve() {
	ll n,m,q; cin >> n >> m >> q;
	F0R(ind,m) states[ind].s=ind;
	ll city;
	F0R(_,n) {
		cin >> city;
		++states[city-1].f;
	}
	F0R(ind,q) {
		cin >> queries[ind].f;
		--queries[ind].f;
		queries[ind].s=ind;
	}
	sort(queries,queries+q);
	sort(states,states+m);
	ll yrptr = 0;
	ll yr = n;
	ll city_ind = 0;
	ll occs = states[0].f;
	for (; occs==states[city_ind].f; ++city_ind) {
		myTree.insert(states[city_ind].s);
	}
	while (yrptr < q) {
		if (city_ind < m) {
			// new cities
			ll newyr = (states[city_ind].f - occs) * city_ind+yr;
			if (newyr <= queries[yrptr].f) {
				// if we can add new cities in consideration before next cycle
				occs = states[city_ind].f;
				for (; occs==states[city_ind].f; ++city_ind) {
					myTree.insert(states[city_ind].s);
				}
				yr = newyr;
				continue;
			}
		}
		// otherwise we get to year in this cycle
		ll treeInd = (queries[yrptr].f - yr)%city_ind;
		ll newC = *myTree.find_by_order(treeInd);
		anses[queries[yrptr].s] = newC;
		++yrptr;
	}
	F0R(ind,q) {
		cout << anses[ind]+1 << endl;
	}
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO();
	#endif

	solve();
}