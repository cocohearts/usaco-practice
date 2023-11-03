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

int N,W;
vii cows;
vector<pair<ll,ll> > scaledScores;

bool check(int num, int den) {
    // if (num==11000) {
    //     int a = 0;
    // }
    loop(i,N) {
        scaledScores[i] = MP((ll)(cows[i].S)*((ll)den) - ((ll)cows[i].F*(ll)num),cows[i].F);
    }
    sort(scaledScores.rbegin(),scaledScores.rend());
    if (scaledScores[0].F < 0) return false;

    // int startScore, startWeight;
    // startScore = startWeight = 0;
    // loop(i,N) {
    //     // for each i, scores updated to give at each weight the best score achievable
    //     if (scaledScores[i].F > 0) {
    //         startScore += scaledScores[i].F;
    //         startWeight += scaledScores[i].S;
    //     } else break;
    // }
    // if (W<=startWeight) return true;
    vector<ll> scores(W);
    // scores[startWeight] = startScore;
    fill(scores.begin(),scores.end(),LONG_MIN);
    scores[0] = 0L;
    loop(cowInd,N) {
        ll score = scaledScores[cowInd].F;
        ll wt = scaledScores[cowInd].S;
        // if (score <= 0) {
        for (int weightInd=W-1; weightInd>=0; --weightInd) {
            if (scores[weightInd] != LONG_MIN) {
                if (weightInd+wt<W) {
                    {
                        scores[weightInd+wt] = max(scores[weightInd+wt],scores[weightInd]+score);
                    }
                } else if (scores[weightInd]+score >= 0) {
                    return true;
                }
            }
        }
        // }
    }
    return false;
}

int main() {
    // freopen("input","r",stdin);
    freopen("talent.in","r",stdin);
    freopen("talent.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> W;
    int weight,talent;
    loop(i,N) {
        cin >> weight >> talent;
        cows.PB(MP(weight,talent));
    }
    scaledScores.resize(N);

    int top = 10000000;
    int bot = 0;

    loop(i,40) {
        int mid = (top+bot)/2;
        if (check(mid,10000)) {
            bot = mid;
        } else {
            top = mid;
        }
    }
    cout << bot/10;
}