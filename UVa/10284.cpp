#include <bits/stdc++.h>
#include <iostream>
#include <set>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)
#define sloop(e,s) for(auto&& e : s)
#define itloop(it,m) for(auto&& it = m.begin(); it!=m.end(); ++it)
#define F first
#define S second
#define PB push_back
#define MP make_pair

vii search(int i,int j,vector<vector<char>> board,ii dir) {
    vii answer;
    bool toContinue = true;
    if (i<0 || i>=8 || j<0 || j>=8) {
        return answer;
    } else if (board[i][j] != '0') {
        return answer;
    }
    vii nextAnswer = search(i+dir.F,j+dir.S,board,dir);
    nextAnswer.PB(MP(i,j));
    return nextAnswer;
}

int main() {
    // white is UPPERCASE, black is lowercase
    // emptysquare is "0"
    // read 
    // {{,,},
    //  {,,},
    //  ..}
    // freopen("input","r",stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string FENBoard;
    while (cin >> FENBoard) {
        vector<vector<char>> board;
        vector<char> newrow;
        board.PB(newrow);
        sloop (newChar,FENBoard) {
            if (newChar=='/') {
                vector<char> newrow;
                board.PB(newrow);
            } else if (isdigit(newChar)) {
                loop(i,newChar-'0') {
                    board[board.size()-1].PB('0');
                }
            } else board[board.size()-1].PB(newChar);
        }
        vii attacked;
        loop(i,8) {
            loop(j,8) {
                // ref. piece at board[i][j] i.e. ith row, jth column
                if (board[i][j] == '0') {
                    continue;
                }
                set<char> hori = {'r','R','q','Q'};
                set<char> diag = {'b','B','q','Q'};
                attacked.PB(MP(i,j));
                if (board[i][j] == 'p') {
                    attacked.PB(MP(i+1,j-1));
                    attacked.PB(MP(i+1,j+1));
                } else if (board[i][j] == 'P') {
                    attacked.PB(MP(i-1,j-1));
                    attacked.PB(MP(i-1,j+1));
                } else if ((board[i][j] == 'N') || (board[i][j] == 'n')) {
                    loop(x,2) {loop(y,2) {loop(z,2) {
                        int x_mag = x+1;
                        int y_mag = 2-x;
                        int x_dir = y ? x_mag : x_mag * -1;
                        int y_dir = z ? y_mag : y_mag * -1;
                        attacked.PB(MP(i+x_dir,j+y_dir));
                    }}}
                } else if ((board[i][j] == 'k') || (board[i][j] == 'K')) {
                    loop(x,3) {loop(y,3) {
                        attacked.PB(MP(i+x-1,j+y-1));
                    }}
                } else if (hori.find(board[i][j]) != hori.end()) {
                    vii dirs = {{0,1},{0,-1},{1,0},{-1,0}};
                    sloop (dir,dirs) {
                        vii newSquares = search(i+dir.F,j+dir.S,board,dir);
                        attacked.insert(attacked.end(),newSquares.begin(),newSquares.end());
                    }
                }
                if (diag.find(board[i][j]) != diag.end()) {
                    vii dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
                    sloop (dir,dirs) {
                        vii newSquares = search(i+dir.F,j+dir.S,board,dir);
                        attacked.insert(attacked.end(),newSquares.begin(),newSquares.end());
                    }
                }
            }
        }
        vi attackedList(64,0);
        sloop(s,attacked) {
            if (s.F>=0 && s.F<8 && s.S>=0 && s.S<8) {
                attackedList[8*s.F+s.S] = 1;
            }
        }
        int sum=0;
        sloop(state,attackedList) sum += state;
        cout << 64-sum << "\n";
    }
}