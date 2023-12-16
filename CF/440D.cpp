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
	const int L = 15;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 405;
	#define dbg(...)
#endif

vi adj[L];
vector<pair<pi,int>> num_edges;

// best from vertex v with s vertices, not include parent edge
int DP1[L][L];
vi DP2[L][L];
// for child_ind, for size, what is best prev?
int DP3[L][L];
// for v, for size, for child_ind, what is best?
vi choices[L][L];
int parents[L];

int n,k;

void recurse(int v,int p) {
	// for each s, best over distros to s-1 of DP1[c][d] sum
	int DP2ind=0;
	parents[v]=p;
	F0R(s,k+1) {
		DP2[v][s]=vi(adj[v].size(),INF);
		choices[v][s]=vi(adj[v].size(),INF);	
	}
	trav(child,adj[v]) if(child!=p) {
		recurse(child,v);
	}
	trav(child,adj[v]) if(child!=p) {
		if (v==1) {
			int pause=1;
		}
		F0R(subSize,k) {
			int bestsubSubSize=0;
			F0R(subSubSize,subSize+1) {
				if (!DP2ind && subSubSize!=subSize) continue;
				int val = ((DP2ind)?DP2[v][subSize-subSubSize][DP2ind-1]:0)+DP1[child][subSubSize];
				if (DP2[v][subSize][DP2ind]>val) {
					DP2[v][subSize][DP2ind]=val;
					bestsubSubSize=subSubSize;
				}
			}
			DP3[DP2ind][subSize]=bestsubSubSize;
		}
		++DP2ind;
	}
	if (DP2ind) {
		F0R(size,k) {
			DP1[v][size+1]=DP2[v][size][DP2ind-1];
		}
	} else {DP1[v][1]=0;}
	DP1[v][0]=1;
	F0R(SZ,k) {
		int subSize=SZ;
		R0F(child_ind,DP2ind) {
			choices[v][SZ+1][child_ind] = DP3[child_ind][subSize];
			subSize -= DP3[child_ind][subSize];
		}
	}
}

bool printed=false;

void print(int a,int b) {
	if (a>b) swap(a,b);
	int edge_num = lb(all(num_edges),mp(mp(a,b),0))->s;
	if (printed) cout << " ";
	else printed=true;
	cout << edge_num;
}

void find_edges(int v,int p,int sz) {
	int child_ind = 0;
	trav(child,adj[v]) if(child!=p) {
		if (!choices[v][sz][child_ind]) {
			print(v,child);
		}
		else {
			find_edges(child,v,choices[v][sz][child_ind]);
		}
		++child_ind;	
	}
}

void solve() {
	cin >> n >> k;
	int a,b;
	F0R(_,n-1) {
		cin >> a >> b;
		adj[a].pb(b); adj[b].pb(a);
		if (a>b) swap(a,b);
		num_edges.pb(mp(mp(a,b),_+1));
	}
	sort(all(num_edges));
	F0R(x,L) F0R(y,L) DP1[x][y]=INF;
	recurse(1,-1);
	int minAns=INF, minV;
	FOR(nd,1,n+1) {
		if (DP1[nd][k]<minAns) {
			minAns=DP1[nd][k];
			minV=nd;
		}
	}
	cout << (minAns+((minV==1)?0:1)) << endl;
	find_edges(minV,parents[minV],k);
	if (minV!=1) {
		print(minV,parents[minV]);
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