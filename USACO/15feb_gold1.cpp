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
	const int L = 750;
	#define dbg(...)
#endif

struct SegmentTree {
	vi sgtr; int len;
	SegmentTree(int N) {len=N; sgtr = vi(2*N,0);}
	void add(int ind, int val) {
		for(ind+=len; ind>0; ind>>=1) {
			sgtr[ind] += val;
			sgtr[ind] %= MOD;
		}
	}
	int sum(int ind1, int ind2) {
		ll ret = 0;
		for(ind1+=len,ind2+=len; ind2>ind1; ind1>>=1,ind2>>=1) {
			if (ind1%2) ret += sgtr[ind1++];
			if (ind2%2) ret += sgtr[--ind2];
		}
		return (int)(ret % MOD);
	}
};

int grid[L][L];
pair<int,pi> states[L*L];
int sums[L];
int grid_sums[L][L];

void solve() {
	int R,C,K; cin >> R >> C >> K;
	F0R(x,R) F0R(y,C) {
		cin >> grid[x][y];
		states[x*C+y] = mp(grid[x][y],mp(x,y));
	}
	auto special_sort = [](pair<int,pi> p1, pair<int,pi> p2){
		return (mp(p1.f,mp(p1.s.s,p1.s.f)) < mp(p2.f,mp(p2.s.s,p2.s.f)));
	};
	sort(states,states+R*C,special_sort);

	SegmentTree prev(C);
	SegmentTree skipped(R*C);

	F0R(x,R) F0R(y,C) grid_sums[x][y] = 0;
	grid_sums[0][0] = 1;

	F0R(x,R) {
		// clear sums
		F0R(y,C) {
			sums[y] = 0;
		}
		F0R(y,C) {
			int state_ind = lb(states,states+R*C,mp(grid[x][y],mp(x,y)),special_sort) - states;
			// add sums
			if (x*y==0) {
				if (x+y) continue;
				// else x=y=0
				sums[0]=1;
				continue;
			}
			sums[y]	= prev.sum(0,y);
			// subtract previous
			int left_ind = lb(states,states+R*C,mp(grid[x][y],mp(0,0)),special_sort) - states;
			int right_ind = lb(states,states+R*C,mp(grid[x][y],mp(0,y)),special_sort) - states;
			sums[y] += MOD - skipped.sum(left_ind,right_ind);
			sums[y] %= MOD;
		}
		F0R(y,C) {
			int state_ind = lb(states,states+R*C,mp(grid[x][y],mp(x,y)),special_sort) - states;
			skipped.add(state_ind,sums[y]);
		}
		// load onto next
		F0R(y,C) {
			prev.add(y,sums[y]);
		}
	}
	cout << sums[C-1];
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("hopscotch");
	#endif

	solve();
}