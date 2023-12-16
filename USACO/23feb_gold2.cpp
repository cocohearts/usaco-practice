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
	const int L = 200005;
	#define dbg(...)
#endif

vi children[L];
int rates[L];
ll rate_sums[L];
int subt_sums[L];

ll DP[L];
// fDP[v][0]=DP[v], fDP[v][1] means must end on 0
ll fDP[L];

// farthest this subtree can go
int depths[L];
int dists[L];

void recurse(int v) {
	vector<pair<double,int>> ratios;
	rate_sums[v]=rates[v];
	subt_sums[v]=1;
	ll ans=0;
	depths[v]=dists[v];
	trav(child,children[v]) {
		dists[child]=dists[v]+1;
		recurse(child);
		depths[v]=max(depths[v],depths[child]);
		double ratio = (double)subt_sums[child]/(double)rate_sums[child];
		ratios.pb(mp(ratio,child));
		rate_sums[v]+=rate_sums[child];
		subt_sums[v]+=subt_sums[child];
		ans += DP[child];
	}
	sort(all(ratios));
	int time_passed = 1;
	trav(ratio_pair,ratios) {
		ans += time_passed * rate_sums[ratio_pair.s];
		time_passed += 2*subt_sums[ratio_pair.s];
	}
	// compute deltas for fDP
	DP[v]=ans;
	ll best_delta = 1e18;
	ll R_pref=0, S_pref=0;
	R0F(ind,ratios.size()) {
		int child = ratios[ind].s;
		if (depths[child]==depths[v]) {
			ll delta = rate_sums[child]*S_pref-2*subt_sums[child]*R_pref+fDP[child]-DP[child];
			best_delta=min(best_delta,delta);
		}
		R_pref+=rate_sums[child];
		S_pref+=2*subt_sums[child];
	}
	if (best_delta==1e18) {
		best_delta=0;
	}
	fDP[v]=ans+best_delta;
}

// void fancy_recurse(int v) {
// 	// child to do last is that among the deepest with highest size:rate ratio
// 	vector<pair<double,int>> ratios;
// 	ll ans=0;
// 	depths[v]=dists[v];
// 	double best_deepratio=0;
// 	int best_lastchild;
// 	trav(child,children[v]) {
// 		fancy_recurse(child);
// 		depths[v]=max(depths[v],depths[child]);
// 		double ratio = (double)subt_sums[child]/(double)rate_sums[child];
// 		if (depths[v]==depths[child] && ratio>best_deepratio) {
// 			best_lastchild=child;
// 		}
// 		ratios.pb(mp(ratio,child));
// 		ans += DP[child];
// 	}
// 	sort(all(ratios));
// 	int time_passed = 1;
// 	trav(ratio_pair,ratios) {
// 		if (ratio_pair.s==best_lastchild) continue;
// 		ans += time_passed * rate_sums[ratio_pair.s];
// 		time_passed += 2*subt_sums[ratio_pair.s];
// 	}
// 	ans += time_passed * rate_sums[best_lastchild];
// 	fDP[v]=ans;
// }

void solve() {
	int N,T; cin >> N >> T;
	int p;
	FOR(nd,2,N+1) {
		cin >> p >> rates[nd];
		children[p].pb(nd);
	}
	dists[1]=0;
	recurse(1);
	if (!T) {
		cout << 2*(N-1) << " " << DP[1];
	} else {
		cout << 2*(N-1)-depths[1] << " " << fDP[1];
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