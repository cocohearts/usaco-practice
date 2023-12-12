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
	const int L = 100;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 200000;
	#define dbg(...)
#endif

struct SegTree {
	vi sgtr; int len;
	SegTree(int n) {
		len = n; sgtr = vi(2*n,0);
	}
	void add(int ind, int val) {
		for (ind+=len; ind > 0; ind>>=1) {
			sgtr[ind]+=val;
		}
	}

	int sum(int ind1, int ind2) {
		int ret = 0;
		for (ind1+=len, ind2+=len; ind2>ind1; ind1>>=1, ind2>>=1) {
			if (ind1%2) {
				ret += sgtr[ind1++];
			}
			if (ind2%2) {
				ret += sgtr[--ind2];
			}
		}
		return ret;
	}
};

int nums[L];
pair<pi,int> qs[L];
int anses[L];

int vals[L];
int seen[L];

void solve() {
	int n, q; cin >> n >> q;

	F0R(i,n) cin >> nums[i];
	F0R(i,q) {
		cin >> qs[i].f.f >> qs[i].f.s;
		--qs[i].f.f; --qs[i].f.s;
		qs[i].s = i;
	}
	sort(qs,qs+q);

	SegTree sgtr(n);

	F0R(i,n) {
		vals[i] = nums[i];
		seen[i] = -1;
	}
	sort(vals,vals+n);

	int a = n;
	R0F(ind,q) {
		auto quest = qs[ind];
		pi query = quest.f; int qind = quest.s;
		while (a > query.f) {
			--a;
			sgtr.add(a,1);
			int numInd = lb(vals,vals+n,nums[a]) - vals;
			if (numInd < n) if (seen[numInd]!=-1) {
				sgtr.add(seen[numInd],-1);
			}
			seen[numInd] = a;
		}
		anses[qind] = sgtr.sum(query.f,query.s+1);
	}
	F0R(ind,q) {
		cout << anses[ind] << endl;
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