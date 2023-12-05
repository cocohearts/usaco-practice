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
	const int L = 100000;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 200000;
	#define dbg(...)
#endif

int prices[L];
vi p_to_nd[2*L];
vi nd_to_p[L];
int cycles[L][2];
bool visited[2*L];
int N;
pair<int,pi> pairings[2*L];

struct DSU {
	vi g;
	DSU(int n) {g = vi(n,-1);}
	int get(int x) {
		if (g[x]<0) return x;
		g[x] = get(g[x]);
		return g[x];
	}
	int size(int x) {return -1*g[get(x)];}
	bool join(int x, int y) {
		int a=get(x), b=get(y);
		if (a==b) return false;
		if (g[a]>g[b]) swap(a,b);
		g[a] += g[b]; g[b] = a;
		return true;
	}
};

void recurse(int nd, int cycle_num, int p) {
	// p_ind portal came in on, not portal go out on
	int p_ind=0;
	while(nd_to_p[nd][p_ind]!=p) {++p_ind;}
	int cycle_ind = p_ind>=2;
	if (visited[nd+N*cycle_ind]) {return;}
	visited[nd+N*cycle_ind] = true;
	cycles[nd][cycle_ind] = cycle_num;
	if (p_ind<2) {p_ind = 1-p_ind;}
	else {p_ind = 5-p_ind;}
	int newP = nd_to_p[nd][p_ind];
	int newNd;
	trav(nNd,p_to_nd[newP]) {
		if (nNd!=nd) newNd = nNd;
	}
	recurse(newNd,cycle_num,newP);
}

void solve() {
	cin >> N;
	F0R(ind,N) {
		cin >> prices[ind];
		int p;
		F0R(_,4) {
			cin >> p;
			p_to_nd[p].pb(ind);
			nd_to_p[ind].pb(p);
		}
	}
	F0R(ind,2*N) visited[ind] = false;

	int cycle_num = 0;
	F0R(sd,2) F0R(nd,N) {
		cycles[nd][sd]=-1;
	}
	F0R(sd,2) {
		F0R(nd,N) {
			if (!visited[nd+N*sd]) {
				int p = nd_to_p[nd][2*sd];
				recurse(nd,cycle_num,p);
				++cycle_num;
			}
		}
	}
	// all the cycles have been collected, ok
	// now each vertex is an edge between two cycles (possibly) and we want to connect *all* the cycles
	int c1, c2;
	int ind = 0;
	F0R(nd,N) {
		c1 = cycles[nd][0]; c2 = cycles[nd][1];
		if (c1!=c2) {
			pairings[ind] = mp(prices[nd],mp(c1,c2));
			++ind;
		}
	}
	sort(pairings,pairings+ind);
	int cost = 0;
	DSU myDSU(cycle_num+1);
	F0R(pairInd,ind) {
		auto newPair = pairings[pairInd];
		if (myDSU.size(0)==cycle_num+1) break;
		if (myDSU.join(newPair.s.f,newPair.s.s)) {
			cost += newPair.f;
		}
	}
	cout << cost;
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