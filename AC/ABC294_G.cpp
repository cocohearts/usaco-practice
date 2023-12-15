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

vector<pair<pi,int>> adj[L];

pi edge_locs[L];

vi tour;
vi signed_weights;
int first[L]; int last[L];

int edge_weights[L];
int parents[L][32];
int depths[L];
int depth = 0;
int BITS;

void recurse(int v,int p,int in_edge) {
	// complete Euler tour, builds signed_weights, first, last, edge_locs
	parents[v][0]=p;
	depths[v]=depth;
	++depth;
	first[v]=tour.size();
	edge_locs[in_edge].f=tour.size()-1;
	tour.pb(v);
	trav(child,adj[v]) if(child.f.s!=p) {
		signed_weights.pb(child.f.f);
		recurse(child.f.s,v,child.s);
		tour.pb(v);
		signed_weights.pb(-1*child.f.f);
	}
	--depth;
	last[v]=tour.size();
	edge_locs[in_edge].s=tour.size()-1;
}

struct PURS {
	int len; vl sgtr;
	PURS(int N) {len=N;sgtr=vl(2*N,0);}
	void add(int ind, int val) {
		for(ind+=len;ind>0;ind>>=1) {
			sgtr[ind]+=val;
		}
	}
	ll sum(int ind1, int ind2) {
		ll ret=0;
		for(ind1+=len,ind2+=len;ind2>ind1;ind1>>=1,ind2>>=1) {
			if (ind1%2) ret+=sgtr[ind1++];
			if (ind2%2) ret+=sgtr[--ind2];
		}
		return ret;
	}
};

int par(int nd, int k) {
	R0F(ind,BITS) {
		if (k&1<<ind) {
			nd=parents[nd][ind];
		}
	}
	return nd;
}

int LCA(int nd1, int nd2) {
	if (depths[nd1]>depths[nd2]) swap(nd1,nd2);
	nd2=par(nd2,depths[nd2]-depths[nd1]);
	R0F(ind,BITS) {
		int p1=par(nd1,1<<ind),p2=par(nd2,1<<ind);
		if (p1!=p2) {nd1=p1;nd2=p2;}
	}
	return (nd1==nd2)?nd1:parents[nd1][0];
}

void solve() {
	int N; cin >> N;
	int u,v,w;
	FOR(edge_ind,1,N) {
		cin >> u >> v >> w;
		adj[u].pb(mp(mp(w,v),edge_ind));
		adj[v].pb(mp(mp(w,u),edge_ind));
		edge_weights[edge_ind] = w;
	}
	recurse(1,-1,0);
	BITS = 32-__builtin_clz(N);
	F0R(ind,BITS) FOR(nd,1,N+1) {
		if (parents[nd][ind]>0) {
			parents[nd][ind+1]=parents[parents[nd][ind]][ind];
		} else {
			parents[nd][ind+1]=-1;
		}
	}
	PURS edges_sgtr(2*N);
	F0R(ind,2*N-2) {
		edges_sgtr.add(ind,signed_weights[ind]);
	}
	int Q; cin >> Q;
	int sig,i;
	F0R(_,Q) {
		cin >> sig;
		if (sig==1) {
			cin >> i >> w;
			int delta = w-edge_weights[i];
			edges_sgtr.add(edge_locs[i].f,delta);
			edges_sgtr.add(edge_locs[i].s,-1*delta);
			edge_weights[i]=w;
		} else {
			cin >> u >> v;
			int thisLCA=LCA(u,v);
			ll ans = edges_sgtr.sum(first[thisLCA],first[u]);
			ans += edges_sgtr.sum(first[thisLCA],first[v]);
			cout << ans << endl;
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