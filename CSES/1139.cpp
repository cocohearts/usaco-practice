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

struct SegmentTree {
	vi sgtr; int len;
	SegmentTree(int N) {len=N; sgtr=vi(2*N,0);}
	void add(int ind, int val) {
		for(ind+=len; ind>0; ind>>=1) sgtr[ind]+=val;
	}
	int sum(int ind1, int ind2) {
		int ret=0;
		for(ind1+=len,ind2+=len; ind2>ind1; ind1>>=1,ind2>>=1) {
			if (ind1%2) ret += sgtr[ind1++];
			if (ind2%2) ret += sgtr[--ind2];
		}
		return ret;
	}
};

int colors[L];
int sorted[L];
vi adjList[L];
vi tour;
int anses[L];
int first[L];
int last[L];
int last_col_occ[L];

void recurse(int nd, int parent) {
	first[nd] = tour.size();
	tour.pb(nd);
	trav(child,adjList[nd]) {
		if (child!=parent) recurse(child,nd);
	}
	last[nd] = tour.size();
	tour.pb(nd);
}

void solve() {
	int n; cin >> n;
	F0R(i,n) {cin >> colors[i]; sorted[i] = colors[i];}
	sort(sorted,sorted+n);
	F0R(i,n) {colors[i] = lb(sorted,sorted+n,colors[i])-sorted;}
	int a,b;
	F0R(_,n-1) {
		cin >> a >> b;
		--a; --b;
		adjList[a].pb(b); adjList[b].pb(a);
	}
	F0R(i,n) {
		last_col_occ[i]=-1;
	}
	recurse(0,-1);
	SegmentTree SegTree(2*n);
	// now we want to find # distinct colors in range(first[nd],last[nd])
	R0F(ind,2*n) {
		int nd = tour[ind];
		if (first[nd]==ind) {
			// first occ
			SegTree.add(ind,1);
			if (last_col_occ[colors[nd]]!=-1) {
				SegTree.add(last_col_occ[colors[nd]],-1);
			}
			last_col_occ[colors[nd]] = ind;
			anses[nd] = SegTree.sum(ind,last[nd]);
		}
	}
	F0R(i,n) {
		if (i) cout << " ";
		cout << anses[i];
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