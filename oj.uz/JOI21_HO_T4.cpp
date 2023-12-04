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
vi colors[L];
vi sort_cols[L];

vl dists[L];
vb solved[L];
vi col_frqs[L];

void solve() {
	int N,M; cin >> N >> M;
	int A,B,C; ll P;
	F0R(_,M) {
		cin >> A >> B >> C >> P;
		--A; --B; --C;
		adj[A].pb(mp(P,B));
		colors[A].pb(C);
		sort_cols[A].pb(C);
		adj[B].pb(mp(P,A));
		colors[B].pb(C);
		sort_cols[B].pb(C);
	}
	F0R(ind,N) {
		sort(all(sort_cols[ind]));
		int prev = -1;
		int colInd = -1;
		trav(col,sort_cols[ind]) {
			if (prev != col) {
				++colInd;
				prev = col;
				col_frqs[ind].pb(0);
			}
			++col_frqs[ind][colInd];
		}
		sort_cols[ind].erase(unique(all(sort_cols[ind])), sort_cols[ind].end());
		int col_count = sort_cols[ind].size();
		dists[ind] = vl(col_count+1,INF);
		solved[ind] = vb(col_count+1,false);
	}

	priority_queue<pair<ll,pi>, vector<pair<ll,pi>>, greater<pair<ll,pi>>> DijQ;
	DijQ.push(mp(0,mp(-1,0)));

	ll ans = -1;

	while (DijQ.size()) {
		auto nN = DijQ.top(); DijQ.pop();
		ll dist = nN.f; int col = nN.s.f; int nd = nN.s.s;
		if (dist==5L) {
			int k=4;}
		if (dist==7L) {
			int k=3;
		}
		if (nd==N-1) {
			ans = dist;
			break;
		}
		int col_ind = col;
		if (col>=0) {
			col_ind = lb(all(sort_cols[nd]),col)-sort_cols[nd].begin();
		}
		if (solved[nd][col_ind+1]) {
			continue;
		}
		solved[nd][col_ind+1] = true;
		dists[nd][col_ind+1] = dist;
		F0R(ind,adj[nd].size()) {
			int nbN = adj[nd][ind].s; 
			ll eCo = adj[nd][ind].f;
			int nbCol = colors[nd][ind];

			int nbColInd = lb(all(sort_cols[nd]),nbCol)-sort_cols[nd].begin();
			int nbFrq = col_frqs[nd][nbColInd];
			if (nbFrq==1 || (nbFrq==2 && nbCol == col)) {
				// for free
				if (!solved[nbN][0]) {
					DijQ.push(mp(dist,mp(-1,nbN)));
				}
			}
			if (nbFrq==2) {
				F0R(nInd,adj[nd].size()) {
					if (colors[nd][nInd]==nbCol) {
						eCo = min(eCo,adj[nd][nInd].f);
					}
				}
				DijQ.push(mp(dist+eCo,mp(-1,nbN)));
			}
			// pay
			if (!solved[nbN][nbColInd+1]) {
				DijQ.push(mp(dist+eCo,mp(nbCol,nbN)));
			}
		}
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