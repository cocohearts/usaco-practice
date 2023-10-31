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

int P = pow(10,9)+7;

int choose(int A,int B) {
    int exp = 1;
    loop(i,B) {
        exp *= A-i;
        exp /= i+1;
        exp %= P;
    }
    return exp;
}

int sumExp(int N,int M,int k,bool forward) {
    ll answer = 0;
    if (forward) {
        loop(i,min(N+1,k+1)) {
            int j = k-i;
            ll exp = 1;
            if (j<=M) {
                exp *= choose(N,i);
                exp %= P;
                exp *= choose(M,j);
                exp %= P;
                exp *= 1<<max(1,i);
                exp %= P;
                answer += exp;
            }
        }
        return (int)(answer) % P;
    } else {
        return (2*choose(M,k)) % P;
    }
}

int iterate(vi papers, int front, int end, vi chosenIndices, bool forward, int limit) {
    int len = end-front;
    int start = (chosenIndices.size()) ? *chosenIndices.rbegin() : end;
    int k = to_string(limit).length()-chosenIndices.size();
    int pow10 = pow(10,k-1);
    int nextDig = (limit/pow10) % 10;
    int answer = 0;
    if (!k) {
        return 2;
    }
    if (forward) {
        for (int nextIndex = start-1; nextIndex>=front; --nextIndex) {
            if (papers[nextIndex] == nextDig) {
                chosenIndices.PB(nextIndex);
                answer += iterate(papers,front,end,chosenIndices,true,limit);
                chosenIndices.pop_back();
            } else if (papers[nextIndex] < nextDig) {
                int M = end-nextIndex-chosenIndices.size()-1;
                int N = nextIndex-front;
                answer += sumExp(N,M,k-1,true);
            }
        }
    }
    if (chosenIndices.size()) {
        iloop(nextIndex,start+1,end) {
            if (find(chosenIndices.begin(),chosenIndices.end(),nextIndex) != chosenIndices.end()) continue;
            if (papers[nextIndex] == nextDig) {
                chosenIndices.PB(nextIndex);
                answer += iterate(papers,front,end,chosenIndices,false,limit);
                chosenIndices.pop_back();
            } else if (papers[nextIndex] < nextDig) {
                int chosen = 0;
                for (vi::iterator revIt = chosenIndices.begin();(*revIt)>start;++revIt) {
                    ++chosen;
                }
                answer += sumExp(0,end-start-chosen,k-1,false);
            }
        }
    }
    return answer;
}

int main() {
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,A,B;
    vi papers;
    int paper;
    int Q;
    cin >> N >> A >> B;
    int Alen, Blen;
    Alen = to_string(A).length();
    Blen = to_string(B).length();
    loop(i,N) {
        cin >> paper;
        papers.PB(paper);
    }
    // 0-indexed inclusive/exclusive
    cin >> Q;
    int front,end;
    loop(i,Q) {
        cin >> front >> end;
        --front;
        int len = end-front;
        vi chosenIndices;
        ll top = 0;
        ll bot = 0;
        // generate all counts with sub-len
        iloop(i,0,Blen) {
            top += choose(len,i) * (1<<(i) % P);
            top %= P;
        }
        iloop(i,0,Alen) {
            bot += choose(len,i) * (1<<(i) % P);
            bot %= P;
        }
        top += iterate(papers,front,end,chosenIndices,true, B);
        bot += iterate(papers,front,end,chosenIndices,true, A-1);
        int answer = (top - bot) % P;
        cout << answer << "\n";
    }
}