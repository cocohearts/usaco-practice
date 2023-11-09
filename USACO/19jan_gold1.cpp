#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define iloop(x,a,n) for(int x=a; x<n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

int P = 1000000007;
string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int exp(int b,int p) {
    long answer = 1L;
    long pow = b;
    while (p) {
        if (p%2) {
            answer *= pow;
            answer %= P;
        }
        pow *= pow;
        pow %= P;
        p /= 2;
    }
    return (int)answer;
}

int main() {
    // freopen("input","r",stdin);
    freopen("poetry.in","r",stdin);
    freopen("poetry.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    vi classes,DP,sylls,schemeCount(26,0);
    int syll,rhyme;
    char scheme;

    cin >> N >> M >> K;

    loop(word,N) {
        cin >> syll >> rhyme;
        sylls.PB(syll);
        classes.PB(rhyme);
    }

    loop(line,M) {
        cin >> scheme;
        ++schemeCount[alph.find(scheme)];
    }

    DP.PB(1);
    iloop(i,1,K) {
        int newVal = 0;
        sloop(lastSyll,sylls) {
            if (lastSyll <= i) {
                newVal += DP[i-lastSyll];
                newVal %= P;
            }
        }
        DP.PB(newVal);
    }

    vi byClass(N+1,0);
    loop(i,N) {
        byClass[classes[i]] += DP[K-sylls[i]];
        byClass[classes[i]] %= P;
    }
    
    // vector<long> pows(N+1,0);
    // vi powerSums(1,1);
    // loop(pow,M+1) {
    //     long powerSum = 0;
    //     loop(i,N+1) {
    //         pows[i] *= (long)byClass[i];
    //         pows[i] %= P;
    //         powerSum += pows[i];
    //         powerSum %= P;
    //     }
    //     powerSums.PB(powerSum);
    // }

    long answer = 1;
    loop(letter,26) {
        if (!schemeCount[letter]) continue;
        int sum = 0;
        loop(rhymeClass,N+1) {
            sum += exp(byClass[rhymeClass],schemeCount[letter]);
            sum %= P;
        }
        answer *= sum;
        answer %= P;
    }
    cout << (int)answer;
}