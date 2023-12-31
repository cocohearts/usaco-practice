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
	const int L = 100;
#else
	const int L = 100000;
#endif

int Bs[2*L], Es[2*L];
pair<pi,int> pies[2*L];
bool visited[2*L];
int dists[2*L];

void solve() {
	int N,D;
	cin >> N >> D;
	F0R(i,2*N) {
		cin >> pies[i].f.f >> pies[i].f.s;
		Bs[i] = pies[i].f.f; Es[i] = pies[i].f.s;
		pies[i].s = i;
	}
	auto revsort = [](pair<pi,int> p1, pair<pi,int> p2) {
		return (mp(p1.f.s,p1.f.f) < mp(p2.f.s,p2.f.f));
	};
	sort(pies,pies+N,revsort);
	sort(pies+N,pies+2*N);

	queue<int> BFSQ;
	F0R(i,2*N) {
		if ((i<N && Es[i]==0) || (i>=N && Bs[i]==0)) {
			BFSQ.push(i);
			visited[i] = true;
			dists[i] = 1;
		}
		else {
			visited[i] = false;
			dists[i] = -1;
		}
	}
	while (BFSQ.size()) {
		int ind = BFSQ.ft;
		BFSQ.pop();
		pair<pi,int> *start, *end;
		if (ind < N) {
			// after this Bessie gave, so rn Elsie is giving
			start = lb(pies+N,pies+2*N,mp(mp(Bs[ind]-D,0),0));
			end = ub(pies+N,pies+2*N,mp(mp(Bs[ind],INT_MAX),INT_MAX));
		} else {
			// after this Elsie gave, so rn Bessie is giving
			int rating = Es[ind];
			start = lb(pies,pies+N,mp(mp(0,rating-D),0),revsort);
			end = ub(pies,pies+N,mp(mp(INT_MAX,rating),INT_MAX),revsort);
		}
		while (start != end) {
			int newInd = (*start).s;
			if (!visited[newInd]) {
				visited[newInd] = true;
				dists[newInd] = dists[ind]+1;
				BFSQ.push(newInd);
			}
			++start;
		}
	}
	int dist;
	F0R(i,N) {
		dist = dists[i];
		cout << dist << endl;
	}
}

int main() {
	#ifdef LOCAL // call with -DLOCAL
		freopen("../input.txt", "r", stdin);
		freopen("../myoutput.txt", "w", stdout);
		freopen("../debug.txt", "w", stderr);
		#define dbg(...)                                           \
			cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
				<< ": ";                                           \
			dbgh(__VA_ARGS__)
	#else
		setIO("piepie");
		#define dbg(...)
	#endif

	solve();
}