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

struct DSU {
	vi g;
	vvi adj;
	DSU(int N) {g = vi(N,-1); 
				adj = vvi(N);
				};

	int get(int x) {
		return g[x]<0 ? x : get(g[x]);
	}

	int size(int x) {
		return -1*g[get(x)];
	}

	bool join(int x, int y) {
		int a = get(x), b = get(y);
		if (a==b) return false;
		if (g[a]>g[b]) swap(a,b);
		g[a] += g[b];
		g[b] = a;
		adj[a].pb(b);
		return true;
	}

	vi comp(int x) {
		int a = get(x);
		vi ans; queue<int> BFSQ;
		BFSQ.push(a);
		while (BFSQ.size()>0) {
			int val = BFSQ.ft;
			BFSQ.pop();
			ans.pb(val);
			trav(nb,adj[val]) {
				BFSQ.push(nb);
			}
		}
		return ans;
	}
};

#ifdef LOCAL
	const int L = 200000;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 200000;
	#define dbg(...)
#endif

vi admrg[L];
int colors[L];
int predec[L];
DSU myDSU(L);

void merge(int p,int x,int y) {
	// deals only with DSU reps, and sometimes -1
	if (x!=y) {
		if (x == -1 || y == -1) {
			predec[p] = x+y+1;
		} else {
			if (myDSU.join(x,y)) {
				int p2 = myDSU.get(x);
				predec[p] = p2;
				merge(p2,predec[x],predec[y]);
			}
		}
	}
}

void solve() {
	int N,M; cin >> N >> M;
	int a,b;
	F0R(i,M) {
		cin >> a >> b;
		--a; --b;
		admrg[b].pb(a);
	}

	F0R(i,N) {
		predec[i] = -1;
	}

	F0R(i,N) {
		trav(n,admrg[i]) {
			merge(myDSU.get(n),myDSU.get(i),predec[myDSU.get(n)]);
		}
	}

	F0R(ind,N) {
		colors[ind] = 0;
	}
	int Ncolors = 1;
	F0R(ind,N) {
		int rep = myDSU.get(ind);
		if (!colors[rep]) {
			colors[rep] = ++Ncolors;
		}
		cout << colors[rep] << endl;
	}
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("fcolor");
	#endif

	solve();
}