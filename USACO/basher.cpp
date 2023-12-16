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

const int MOD = 1e9 + 7;
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

const int MX=2e5+5;
int T[MX];

template <int SZ> struct LCA {
	static const int BITS = 32 - __builtin_clz(SZ);
	int N, R = 1, cnt = 0, label[SZ];
	vi adj[SZ], cur[SZ];
	vpi CUR[SZ];
	int par[BITS][SZ], depth[SZ];
	// INITIALIZE
	void addEdge(int u, int v) { adj[u].pb(v), adj[v].pb(u); }
	void dfs(int u, int prev) {
		label[u] = cnt++;
		cur[T[u]].pb(u);
		CUR[T[u]].pb({label[u], u});
		par[0][u] = prev;
		depth[u] = depth[prev] + 1;
		trav(v, adj[u]) if (v != prev) dfs(v, u);
		cur[T[u]].pop_back();
		CUR[T[u]].pb({cnt, sz(cur[T[u]]) ? cur[T[u]].back() : 0});
	}
	void init(int _N) {
		N = _N;
		dfs(R, 0);
		FOR(k, 1, BITS) FOR(i, 1, N + 1) par[k][i] = par[k - 1][par[k - 1][i]];
	}
	// QUERY
	int getPar(int a, int b) {
		R0F(k, BITS) if (b & (1 << k)) a = par[k][a];
		return a;
	}
	int lca(int u, int v) {
		if (depth[u] < depth[v]) swap(u, v);
		u = getPar(u, depth[u] - depth[v]);
		R0F(k, BITS) if (par[k][u] != par[k][v]) u = par[k][u], v = par[k][v];
		return u == v ? u : par[0][u];
	}
	int dist(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}
	int last(int a, int c) {
		auto it = ub(all(CUR[c]), mp(label[a], MOD));
		if (it == begin(CUR[c])) return 0;
		return prev(it)->s;
	}
};

LCA<MX> myLCA;
int N, M, co;

void solve() {
	cin >> N >> M;
	FOR(i,1,N+1) cin >> T[i];
	F0R(i, N - 1) {
		int X, Y;
		cin >> X, Y;
		myLCA.addEdge(X, Y);
	}
	myLCA.init(N);
	F0R(i, M) {
		int A, B, C;
		cin >> A >> B >> C;
		int z = myLCA.lca(A, B);
		int a = myLCA.last(A, C);
		if (a && myLCA.depth[a] >= myLCA.depth[z]) {
			cout << "1";
			continue;
		}
		a = myLCA.last(B, C);
		if (a && myLCA.depth[a] >= myLCA.depth[z]) {
			cout << "1";
			continue;
		}
		cout << "0";
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