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
const int INF = 1e9;
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

vi adj[L];
int DP[L][3];
vi choices[L];

void recurse(int v,int p) {
	F0R(ind,3) DP[v][ind]=0;
	int ct=0;
	trav(child,adj[v]) if(child!=p) {
		recurse(child,v);
		DP[v][0]+=DP[child][2];
		if (DP[child][1]==DP[child][2]&&ct<2) {
			FOR(ind,ct+1,3) --DP[v][ind];
			++ct;
			choices[v].pb(child);
		}
	}
	FOR(ind,1,3) DP[v][ind]+=DP[v][0];
	sort(all(choices[v]));
}

vpi removed;
vpi sticks;

int segments(int v,int p,bool attached=false) {
	vi ends;
	trav(child,adj[v]) if(child!=p) {
		auto ptr = lb(all(choices[v]),child);
		if (ptr==choices[v].end()) {
			removed.pb(mp(child,v));
			segments(child,v);
		} else if (*ptr!=child) {
			removed.pb(mp(child,v));
			segments(child,v);
		} else {
			ends.pb(segments(child,v,true));
		}
	}
	if (attached) return (ends.size())?ends[0]:v;
	else {
		while(ends.size()<2) ends.pb(v);
		sticks.pb(mp(ends[0],ends[1]));
	}
	return 0;
}

void solve() {
	int t; cin >> t;
	F0R(tC,t) {
		int n; cin >> n;
		removed.clear(); sticks.clear();
		F0R(ind,n+1) {adj[ind].clear(); choices[ind].clear();}
		int a,b;
		F0R(_,n-1) {
			cin >> a >> b;
			adj[a].pb(b);
			adj[b].pb(a);
		}
		recurse(1,-1);
		segments(1,-1);
		cout << removed.size() << endl;
		assert(removed.size()==sticks.size()-1);
		F0R(ind,removed.size()) {
			cout << removed[ind].f << " " << removed[ind].s << " " << sticks[ind].s << " " << sticks[ind+1].f << endl;
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