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

int numScores, target;
vi scores;
vi bestScores;
vi curScores;
vi curScoreIndex;
bool solved;

void iterate() {
    if (bestScores.size() > curScores.size()) {
        if (!target) {
            bestScores = curScores;
        } else {
            int start = (curScoreIndex.size()) ? curScoreIndex[curScoreIndex.size()-1] : 0;
            iloop(nextIndex,start,numScores) {
                if (scores[nextIndex] <= target) {
                    curScores.PB(scores[nextIndex]);
                    curScoreIndex.PB(nextIndex);
                    target -= scores[nextIndex];
                    iterate();
                    curScores.pop_back();
                    curScoreIndex.pop_back();
                    target += scores[nextIndex];
                }
            }
        }
    }
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numCases;
    cin >> numCases;
    loop(caseNum,numCases) {
        cout << "Case " << caseNum+1 << ": ";
        cin >> numScores >> target;
        scores.clear();
        int newScore;
        loop(i,numScores) {
            cin >> newScore;
            scores.PB(newScore);
        }
        sort(scores.begin(),scores.end(),greater<int>());
        curScoreIndex.clear();
        bestScores.resize(target);
        iterate();
        if (bestScores.size() < target) {
            cout << "[" << bestScores.size() << "] ";
            loop(i,bestScores.size()) {
                cout << bestScores[i];
                if (i!=bestScores.size()-1) {
                    cout << " ";
                } else {cout << "\n";}
            }
        } else cout << "impossible\n";
    }
}