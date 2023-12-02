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
const ll INF = 1e18;  // not too close to LLONG_MAX
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

vpi adj[L];
bool solved[L];
ll dists[L];
int numRoutes[L];
int minCt[L];
int maxCt[L];

void solve() {
	int n,m; cin >> n >> m;
	int a,b;
	ll c;
	F0R(_,m) {
		cin >> a >> b >> c;
		--a; --b;
		adj[a].pb(mp(c,b));
	}
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> DijQ;
	F0R(ind,n) {
		solved[ind] = false;
		dists[ind] = INF;
		numRoutes[ind] = 0;
		minCt[ind] = 1e9;
		maxCt[ind] = 0;
	}
	dists[0] = 0;
	numRoutes[0] = 1;
	minCt[0] = maxCt[0] = 0;
	DijQ.push(mp(0,0));
	while (DijQ.size()) {
		pair<ll,int> nN = DijQ.top(); DijQ.pop();
		ll dist = nN.f; int nd = nN.s;
		if (solved[nd]) continue;
		solved[nd] = true;
		trav(nb,adj[nd]) {
			int nbN = nb.s;
			if (!solved[nbN]) {
				ll nbDist = dist+nb.f;
				if (nbDist<dists[nbN]) {
					dists[nbN] = nbDist;
					DijQ.push(mp(nbDist,nbN));
					numRoutes[nbN] = numRoutes[nd];
					minCt[nbN] = minCt[nd]+1;
					maxCt[nbN] = maxCt[nd]+1;
				} else if (nbDist==dists[nbN]) {
					numRoutes[nbN] += numRoutes[nd];
					numRoutes[nbN] %= MOD;
					minCt[nbN] = min(minCt[nbN],minCt[nd]+1);
					maxCt[nbN] = max(maxCt[nbN],maxCt[nd]+1);
				}
			}
		}
	}
	cout << dists[n-1] << " " << numRoutes[n-1] << " " << minCt[n-1] << " " << maxCt[n-1];
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