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

struct DSU {
	vi g;
	DSU(int n) {
		g = vi(n,-1);
	}
	int get(int x) {
		return ((g[x]<0)? x : get(g[x]));
	}
	int size(int x) {
		return ((g[x]<0)? -g[x] : size(get(x)));
	}
	int unite(int x, int y) {
		int a = get(x), b = get(y);
		if (a==b) return false;
		if (g[a]>g[b]) swap(a,b);
		g[a] += g[b]; g[b]=a;
		return true;
	}
};

pair<pi,int> queries[L];
pair<pi,int> edges[L];
int anses[L];

void solve() {
	int N,Q;
	cin >> N >> Q;
	F0R(i,N-1) {
		cin >> edges[i].f.f >> edges[i].f.s >> edges[i].s;
	}
	sort(edges,edges+N,[](pair<pi,int> e1, pair<pi,int> e2) {
		return (e1.s > e2.s);
	});
	F0R(i,Q) {
		cin >> queries[i].f.f >> queries[i].f.s;
		queries[i].s = i;
	}
	sort(queries,queries+Q,[](pair<pi,int> q1, pair<pi,int> q2) {
		return q1.f > q2.f;
	});

	int v,k;
	DSU myDSU(N);
	int indE = 0;
	F0R(ind,Q) {
		k = queries[ind].f.f, v = queries[ind].f.s;
		while (indE < N-1 && edges[indE].s >= k) {
			myDSU.unite(edges[indE].f.f,edges[indE].f.s);
			++indE;
		}
		anses[queries[ind].s] = myDSU.size(v)-1;
	}
	F0R(ind,Q) {
		cout << anses[ind] << endl;
	}
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("mootube");
	#endif

	solve();
}