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

vector<pair<ll,int>> adj[L];
vi preds[L];
ll dists[L];
bool solved[L];

ll Udists[L];
ll Vdists[L];

ll Umins[L];
ll Vmins[L];

void Dijkstra(int U, int N, ll Dists[L]) {
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> DijQ;
	DijQ.push(mp(0,U));
	F0R(ind,N) {
		Dists[ind] = INF;
		solved[ind] = false;
	}
	Dists[U] = 0;

	while(DijQ.size()) {
		pair<ll,int> newN = DijQ.top(); DijQ.pop();
		ll dist = newN.f; int nd = newN.s;
		if (solved[nd]) continue;
		solved[nd] = true;
		trav(nb,adj[nd]) {
			int nbN = nb.s;
			if (!solved[nbN]) {
				ll nbDist = dist+nb.f;
				if (nbDist < Dists[nbN]) {
					Dists[nbN] = nbDist;
					DijQ.push(mp(nbDist,nbN));
				}
			}
		}
	}
}

ll recurse(int nd, ll Dists[L], ll Mins[L]) {
	// Mins[V] is minimum of Dists for all preds of V
	if (Mins[nd] != INF) return Mins[nd];
	ll ans = Dists[nd];
	trav(pred,preds[nd]) {
		ans = min(ans,recurse(pred,Dists,Mins));
	}
	Mins[nd] = ans;
	return ans;
}

void solve() {
	int N,M,S,T,U,V; cin >> N >> M >> S >> T >> U >> V;
	--S; --T; --U; --V;

	int a,b;
	ll c;
	F0R(_,M) {
		cin >> a >> b >> c;
		--a; --b;
		adj[a].pb(mp(c,b));
		adj[b].pb(mp(c,a));
	}
	// Dijkstra from S, tracking possible predecessors
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> DijQ;
	DijQ.push(mp(0,S));
	F0R(ind,N) {
		dists[ind] = INF;
		solved[ind] = false;
	}
	dists[S] = 0;

	while(DijQ.size()) {
		pair<ll,int> newN = DijQ.top(); DijQ.pop();
		ll dist = newN.f; int nd = newN.s;
		if (solved[nd]) continue;
		solved[nd] = true;
		trav(nb,adj[nd]) {
			int nbN = nb.s;
			if (!solved[nbN]) {
				ll nbDist = dist+nb.f;
				if (nbDist < dists[nbN]) {
					dists[nbN] = nbDist;
					preds[nbN] = vi(1,nd);
					DijQ.push(mp(nbDist,nbN));
				} else if (nbDist==dists[nbN]) {
					preds[nbN].pb(nd);
				}
			}
		}
	}
	
	// Dijkstra from U and V
	Dijkstra(U,N,Udists);
	Dijkstra(V,N,Vdists);

	F0R(ind,N) {
		Umins[ind] = Vmins[ind] = INF;
	}

	// find min among all preds
	recurse(T,Udists,Umins);
	recurse(T,Vdists,Vmins);

	ll ans = Udists[V];

	F0R(ind,N) {
		ans = min(ans,Udists[ind]+Vmins[ind]);
		ans = min(ans,Vdists[ind]+Umins[ind]);
	}

	cout << ans;
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