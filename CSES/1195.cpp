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
const ll INF = 1e18;
// const int INF = 1e9;  // not too close to LLONG_MAX
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

void solve() {
	int n,m;
	cin >> n >> m;
	vpi adj[L];
	int a,b,w;
	F0R(_,m) {
		cin >> a >> b >> w;
		adj[a-1].pb(mp(w,b-1));
	}
	// 2n states
	priority_queue<pair<pair<ll,int>,bool>,vector<pair<pair<ll,int>,bool>>, greater<pair<pair<ll,int>,bool>>> DijQ;
	bool solved[2*L];
	ll dists[2*L];
	F0R(i,2*n) {
		solved[i] = false;
		dists[i] = INF;
	} 
	DijQ.push(mp(mp(0L,0),false));
	dists[0] = 0;
	while (DijQ.size()) {
		pair<pair<ll,int>,bool> newN = DijQ.top();
		DijQ.pop();
		int ind = newN.f.s + newN.s*n;
		if (!solved[ind]) {
			solved[ind] = true;
			int node = newN.f.s;
			ll dist = newN.f.f;
			bool discounted = newN.s;
			trav(nb,adj[node]) {
				int nbInd = nb.s + discounted*n;
				ll nbDist = dist+((ll)nb.f);
				if (!solved[nbInd]) {
					if (nbDist < dists[nbInd]) {
						DijQ.push(mp(mp(nbDist,nb.s),discounted));
						dists[nbInd] = nbDist;
					}
				}
				if (!discounted) {
					nbInd += n;
					nbDist = dist+((ll)(nb.f)/2);
					if (!solved[nbInd]) {
						if (nbDist < dists[nbInd]) {
							DijQ.push(mp(mp(nbDist,nb.s),true));
							dists[nbInd] = nbDist;
						}
					}
				}
			}
		}
	}
	cout << dists[2*n-1];
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