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
	const int L = 100;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 30000;
	#define dbg(...)
#endif

int Aarr[L+1], Barr[L+1];
pi segs[2*L];

void solve() {
	int A,B,n,m;
	cin >> A >> B >> n >> m;
	F0R(i,n) cin >> Aarr[i];
	F0R(i,m) cin >> Barr[i];
	sort(Aarr,Aarr+n);
	sort(Barr,Barr+m);
	Aarr[n] = A; Barr[m] = B;
	R0F(ind,n) {
		Aarr[ind+1] = Aarr[ind+1]-Aarr[ind];
	}
	R0F(ind,m) {
		Barr[ind+1] = Barr[ind+1]-Barr[ind];
	}
	F0R(ind,n+1) {
		segs[ind] = mp(Aarr[ind],0);
	}
	F0R(ind,m+1) {
		segs[ind+n+1] = mp(Barr[ind],1);
	}
	sort(segs,segs+m+n+2);
	int edges = 0, rows = 0, cols = 0;
	ll ans = 0;
	trav(myPair,segs) {
		int cost = myPair.f; bool Bseg = myPair.s;
		int count;
		if (Bseg) {
			count = n;
			if (rows) {
				count -= max(0,cols-1);
			}
			++rows;
		} else {
			count = m;
			if (cols) {
				count -= max(0,rows-1);
			}
			++cols;
		}
		ans += (ll)count * (ll)cost;
		edges += count;
	}
	cout << ans;
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
		setIO("fencedin");
	#endif

	solve();
}