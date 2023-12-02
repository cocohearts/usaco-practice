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
	const int L = 50000;
	#define dbg(...)
#endif

vpi adj[L];
int hay[L];
int dists[2*L];
bool solved[2*L];

void solve() {
	// equivalently, walk out from barn, at some haybale you can subtract from given time
	int N,M,K; cin >> N >> M >> K;
	int a,b,t;
	F0R(_,M) {
		cin >> a >> b >> t;
		--a; --b;
		adj[a].pb(mp(t,b));
		adj[b].pb(mp(t,a));
	}
	F0R(ind,N) {
		hay[ind] = 0;
	}
	int hay_loc,y;
	F0R(_,K) {
		cin >> hay_loc >> y;
		--hay_loc;
		hay[hay_loc] = max(hay[hay_loc],y);
	}

	// index is node (+ N) if already eaten hay
	F0R(ind,2*N) {
		dists[ind] = INF;
		solved[ind] = 0;
	}
	priority_queue<pi,vpi,greater<pi>> DijQ;
	DijQ.push(mp(0,N-1));
	dists[N-1] = 0;
	while(DijQ.size()) {
		pi nN = DijQ.top(); DijQ.pop();
		if (solved[nN.s]) continue;
		solved[nN.s] = true;
		int dist = nN.f;
		int nd = nN.s%N; bool eaten = nN.s>=N;
		trav(nb,adj[nd]) {
			int nbN = nb.s + N*eaten;
			int nbDist = dist+nb.f;
			if (!solved[nbN] && nbDist < dists[nbN]) {
				dists[nbN] = nbDist;
				DijQ.push(mp(nbDist,nbN));
			}
			if (!eaten && (hay[nbN]!=0)) {
				nbDist -= hay[nbN];
				nbN += N;
				if (!solved[nbN] && nbDist < dists[nbN]) {
					dists[nbN] = nbDist;
					DijQ.push(mp(nbDist,nbN));
				}
			}
		}
	}
	F0R(ind,N-1) {
		int ans = dists[ind+N] <= dists[ind];
		cout << ans << endl;
	}
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("dining");
	#endif

	solve();
}