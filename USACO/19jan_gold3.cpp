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
	const int L = 10000;
	#define dbg(...)
#endif

int cowCt[L];
vpi adj[L];
int pred[L];
bool solved[L];
int dists[L];

int childCt[L];
vi succs[L];

int recurse(int n) {
	childCt[n] = cowCt[n];
	trav(child,succs[n]) {
		childCt[n] += recurse(child);
	}
	return childCt[n];
}

void solve() {
	int N,M,T;
	cin >> N >> M >> T;
	F0R(i,N) {
		cin >> cowCt[i];
	}
	int a,b,t;
	F0R(_,M) {
		cin >> a >> b >> t;
		--a; --b;
		adj[a].pb(mp(t,b));
		adj[b].pb(mp(t,a));
	}
	// Dijkstra, but also track which nodes each of the minimal paths came from in pred
	priority_queue<pi,vpi,greater<pi>> DijQ;
	DijQ.push(mp(0,0));
	F0R(ind,N) {
		solved[ind] = false;
		dists[ind] = INF;
		pred[ind] = -1;
	}
	dists[0] = 0;
	while(DijQ.size()) {
		pi nN = DijQ.top(); DijQ.pop();
		int dist = nN.f; int nd = nN.s;
		if (solved[nd]) continue;
		solved[nd] = true;
		trav(nb,adj[nd]) {
			int nbN = nb.s;
			if (!solved[nbN]) {
				int nbDist = dist+nb.f;
				if (nbDist<dists[nbN]) {
					dists[nbN] = nbDist;
					DijQ.push(mp(nbDist,nbN));
					pred[nbN] = nd;
				} else if (nbDist == dists[nbN]) {
					pred[nbN] = min(pred[nbN],nd);
				}
			}
		}
	}
	F0R(ind,N) {
		if(pred[ind]>=0) {
			succs[pred[ind]].pb(ind);
		}
	}
	recurse(0);

	ll ans = 0;
	F0R(nd,N) {
		ll newAns = (ll)(dists[nd]-T) * ((ll)childCt[nd]);
		ans = max(newAns,ans);
	}
	cout << ans;
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("shortcut");
	#endif

	solve();
}