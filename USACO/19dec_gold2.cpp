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
	const int L = 10;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 100005;
	#define dbg(...)
#endif

int types[L];
int cnt;
int first[L];
int last[L];
vi adjList[L];

vi col_first[L];
vi col_last[L];

int BITS;
int par[L][32];
int hts[L];
int ht=0;

void recurse(int nd, int pa) {
	first[nd] = cnt;
	par[nd][0] = pa;
	hts[nd]=ht++;
	col_first[types[nd]].pb(cnt);
	++cnt;
	trav(child,adjList[nd]) {
		if (child!=pa) recurse(child,nd);
		++cnt;
	}
	--ht;
	col_last[types[nd]].pb(cnt);
	last[nd] = cnt;
}

int getPar(int nd, int p) {
	R0F(i,BITS) if (p&1<<i) nd=par[nd][i];
	return nd;
}

int LCA(int a,int b) {
	if (hts[a]>hts[b]) swap(a,b);
	b = getPar(b,hts[b]-hts[a]);
	R0F(i,BITS) {
		if (par[a][i]!=par[b][i]) {
			a=par[a][i];
			b=par[b][i];
		}
	}
	return (a==b)?a : par[a][0];
}

void solve() {
	int N,M; cin >> N >> M;
	FOR(i,1,N+1) {cin >> types[i];}
	int a,b;
	F0R(_,N-1) {
		cin >> a >> b;
		adjList[a].pb(b);
		adjList[b].pb(a);
	}
	recurse(1,0);
	par[0][0]=0;
	BITS = 32-__builtin_clz(N);
	F0R(i,BITS-1) {
		FOR(nd,1,N+1) {
			par[nd][i+1]=par[par[nd][i]][i];
		}
	}
	int A,B,C;
	F0R(_,M) {
		cin >> A >> B >> C;
		int myLCA=LCA(A,B);
		int ans = 0;
		F0R(ind,2) {
			int v = ind?A:B;
			ans += ub(all(col_first[C]),first[v]) - lb(all(col_first[C]),first[myLCA]);
			ans -= ub(all(col_last[C]),first[v]) - lb(all(col_last[C]),first[myLCA]);
		}
		ans += types[myLCA]==C;
		cout << (int)(ans>0);
	}
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("milkvisits");
	#endif

	solve();
}