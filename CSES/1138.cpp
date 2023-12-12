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
	vl sgtr; int len;
	SegmentTree(int N) {len=N; sgtr=vl(2*N,0);}
	void update(int ind1, int ind2, int val) {
		for(ind1+=len,ind2+=len; ind2>ind1; ind1>>=1,ind2>>=1) {
			if (ind1%2) sgtr[ind1++]+=val;
			if (ind2%2) sgtr[--ind2]+=val;
		}
	}
	ll get(int ind) {
		ll ret = 0;
		for(ind+=len; ind>0; ind>>=1) {
			ret += sgtr[ind];
		}
		return ret;
	}
};

int vals[L];
vi adjList[L];

vi tour;
int first[L];
int last[L];

void recurse(int nd, int pt) {
	first[nd] = tour.size();
	tour.pb(nd);
	trav(child,adjList[nd]) {
		if (child!=pt) recurse(child,nd);
	}
	last[nd] = tour.size();
	tour.pb(nd);
}

void solve() {
	int n,q; cin >> n >> q;
	F0R(i,n) cin >> vals[i];
	int a,b;
	F0R(_,n-1) {
		cin >> a >> b;
		--a; --b;
		adjList[a].pb(b);
		adjList[b].pb(a);
	}
	recurse(0,-1);

	SegmentTree SegTree(2*n);
	F0R(i,n) {
		SegTree.update(first[i],last[i],vals[i]);
	}
	int type,nd,x; 
	F0R(_,q) {
		cin >> type;
		if (type==1) {
			cin >> nd >> x;
			--nd;
			SegTree.update(first[nd],last[nd],x-vals[nd]);
			vals[nd] = x;
		} else {
			cin >> nd;
			--nd;
			cout << SegTree.get(first[nd]) << endl;
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