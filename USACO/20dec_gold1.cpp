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
const int dx[4] = {1, 0, -1, 0},
          dy[4] = {0, 1, 0, -1};  // for every grid problem!!

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

constexpr int pct(int x) { return __builtin_popcount(x); }
constexpr int bits(int x) {
	return x == 0 ? 0 : 31 - __builtin_clz(x);
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
	const int L = 1000;
	#define dbg(...)                                           \
		cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
			<< ": ";                                           \
		dbgh(__VA_ARGS__)
#else
	const int L = 1000;
	#define dbg(...)
#endif

// const pi mx[4] = {{1,0},{0,1},{-1,0},{0,-1}},
//          my[4] = {{0,1},{-1,0},{0,-1},{1,0}};

// void mark(bool rO[][L], pi loc, int d, int N) {
// 	// marks all taxicab dist d from loc as True
// 	F0R(ind,4) {
// 		F0R(x,d) {
// 			int y = d-x;
// 			int Rx = loc.f + mx[ind].f*x + my[ind].f*y;
// 			int Ry = loc.s + mx[ind].s*x + my[ind].s*y;
// 			if (Rx>=0 && Rx<N && Ry>=0 && Ry<N) {
// 				rO[Rx][Ry] = true;
// 			}
// 		}
// 	}
// }

// 1 if rock is there
bool rocks[L][L];
bool visited[L][L];

bool Rvisited[L][L];
int dists[L][L];

int rad[L][L];

vpi adj(pi loc, int N) {
	vpi ans;
	F0R(ind,4) {
		int x = loc.f+dx[ind];
		int y = loc.s+dy[ind];
		if (x>=0 && x<N && y>=0 && y<N) {
			ans.pb(mp(x,y));
		}
	}
	return ans;
}

void solve() {
	int N,D; cin >> N >> D;
	char nextChar;
	queue<pi> StartQ;
	F0R(x,N) F0R(y,N) {
		cin >> nextChar;
		rocks[x][y] = (nextChar == '#');
		if (nextChar=='S') {
			StartQ.push(mp(x,y));
			visited[x][y] = true;
			rad[x][y] = 1;
		} else {
			visited[x][y] = false;
			rad[x][y] = 0;
		}
	}

	queue<pi> RockQ;

	// first find distances to rocks
	F0R(x,N) F0R(y,N) {
		if (rocks[x][y]) {
			RockQ.push(mp(x,y));
			Rvisited[x][y] = true;
			dists[x][y] = 0;
		} else {
			Rvisited[x][y] = false;
		}
	}
	while (RockQ.size()) {
		pi newLoc = RockQ.ft;
		RockQ.pop();
		vpi next = adj(newLoc,N);
		trav(nexLoc,next) {
			int x = nexLoc.f; int y = nexLoc.s;
			if (!Rvisited[nexLoc.f][nexLoc.s]) {
				dists[nexLoc.f][nexLoc.s] = dists[newLoc.f][newLoc.s]+1;
				Rvisited[x][y] = true;
				RockQ.push(nexLoc);
			}
		}
	}

	StartQ.push(mp(-1,0));
	int hours = 0;
	while (StartQ.size()) {
		pi newLoc = StartQ.ft;
		StartQ.pop();
		if (newLoc.f < 0) {
			if (StartQ.size()) {
				++hours;
				StartQ.push(mp(-1,0));
			}
			continue;
		}
		// rad[newLoc.f][newLoc.s] = min(dists[newLoc.f][newLoc.s],hours/D+1);
		vpi next = adj(newLoc,N);
		trav(nexLoc,next) {
			int x = nexLoc.f; int y = nexLoc.s;
			if (!visited[x][y] && (dists[x][y] >= hours/D+1)) {
				rad[x][y] = dists[x][y];
				visited[x][y] = true;
				if (dists[x][y] >= (hours+1)/D+1) {
					StartQ.push(nexLoc);
				}
			}
		}
	}
	// now rad[x][y] is radius of smallest machine clump that can be found at that loc
	// want to find how many squares are covered by it
	queue<pi> BFSQ;
	
	F0R(x,N) F0R(y,N) {
		if (rad[x][y]>0) {
			BFSQ.push(mp(x,y));
			visited[x][y] = true;
		} else {
			visited[x][y] = false;
		}
	}
	while (BFSQ.size()) {
		pi newLoc = BFSQ.ft;
		BFSQ.pop();
		vpi next = adj(newLoc,N);
		int val = rad[newLoc.f][newLoc.s];
		trav(nexLoc,next) {
			int x = nexLoc.f; int y = nexLoc.s;
			val = max(val,rad[x][y]-1);
		}
		if (val>0) {
			trav(nexLoc,next) {
				int x = nexLoc.f; int y = nexLoc.s;
				if (!visited[x][y]) {
					BFSQ.push(nexLoc);
					visited[x][y] = true;
				} 
			}
		}
		rad[newLoc.f][newLoc.s] = val;
	}

	int ans = 0;
	F0R(x,N) F0R(y,N) {
		ans += (rad[x][y]>0);
	}
	cout << ans;
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
	#else
	 	// TODO
		setIO();
	#endif

	solve();
}