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
	const int L = 10;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 200;
	#define dbg(...)
#endif

bool land[L][L];
bool rows[L][L][L];
bool cols[L][L][L];

void solve() {
	int N,M; cin >> N >> M;
	char newC;
	F0R(x,N) F0R(y,M) {
		cin >> newC;
		land[x][y] = newC=='X';
	}
	// rows a,b,x is (a,x) to (b,x)
	// cols a,b,x is (x,a) to (x,b)
	F0R(x,M) F0R(a,N) {
		bool works=true; 
		FOR(b,a,N) {
			if (land[b][x]) works=false;
			cols[a][b][x] = works;
		}
	}
	F0R(x,N) F0R(a,M) {
		bool works=true; 
		FOR(b,a,M) {
			if (land[x][b]) works=false;
			rows[a][b][x] = works;
		}
	}
	int ans = 0;
	F0R(x1,N) FOR(x2,x1+1,N) {
		// find longest seq a-b s.t. cols[x1][x2][a],[x1][x2][b] and rows[a][b][x1], cols[a][b][x2]
		int a=0, b=0;
		while (b<M) {
			if (!(rows[a][b][x1] && rows[a][b][x2] && cols[x1][x2][a])) {
				++b;
				a=b;
			} else {
				if (cols[x1][x2][b]) {
					ans = max((x2-x1+1)*(b-a+1),ans);
				}
				++b;
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
		setIO("fortmoo");
	#endif

	solve();
}