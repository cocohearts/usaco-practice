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

// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// template <class T>
// using Tree =
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
	const int L = 200000;
	#define dbg(...)
#endif

int nums[L];
pair<pi,bool> queries[L];
vi inds;

struct SegmentTree {
	vi sgtr; int len; 
	SegmentTree(int N) : sgtr(N * 2, 0), len(N) {}
	void add(int ind, int val) {
		for (ind+=len; ind>0; ind>>=1) {
			sgtr[ind] += val;
		}
	}
	int sum(int ind1, int ind2) {
		int ret = 0;
		for (ind1+=len, ind2+=len; ind2>ind1; ind1>>=1, ind2>>=1) {
			if (ind1%2) {
				ret += sgtr[ind1++];
			}
			if (ind2%2) {
				ret += sgtr[--ind2];
			}
		}
		return ret;
	}
};

void solve() {
	int n, q; cin >> n >> q;
	F0R(i,n) {cin >> nums[i]; --nums[i];}

	string sig;
	int a, b;
	F0R(i,q) {
		cin >> sig >> a >> b;
		queries[i].s = sig=="?";
		queries[i].f.f = a-1; queries[i].f.s = b;
		if (!queries[i].s) {--queries[i].f.s;}
	}
	F0R(i,n) {
		inds.pb(nums[i]);
	}
	F0R(i,q) {
		if (queries[i].s) inds.pb(queries[i].f.f);
		inds.pb(queries[i].f.s);
	}
	sort(all(inds));
	F0R(i,n) {
		nums[i] = lb(all(inds),nums[i]) - inds.begin();
	}
	F0R(i,q) {
		queries[i].f.s = lb(all(inds),queries[i].f.s) - inds.begin();
		if (queries[i].s) queries[i].f.f = lb(all(inds),queries[i].f.f) - inds.begin();
	}
	SegmentTree SegTree(inds.size());
	F0R(i,n) {
		SegTree.add(nums[i],1);
	}
	F0R(i,q) {
		if (!queries[i].s) {
			// salary change
			int k = queries[i].f.f;
			int x = queries[i].f.s;
			SegTree.add(nums[k],-1);
			SegTree.add(x,1);
			nums[k] = x;
		} else {
			cout << SegTree.sum(queries[i].f.f, queries[i].f.s) << endl;
		}
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