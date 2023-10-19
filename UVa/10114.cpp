#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef long long        ll;
typedef pair<int, int>   ii;
typedef vector<ii>      vii;
typedef vector<int>      vi;

#define INF 1000000000
#define loop(x,n) for(int x = 0; x < n; ++x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int months, record_len;
        float payment, down, loan;
        vector<pair<int, float> > records;
        records.clear();
        cin >> months >> down >> loan >> record_len;
        if (months < 0) {
            return 0;
        }
        payment = (loan)/months;
        loop(i,record_len) {
            int month;
            float rate;
            cin >> month >> rate;
            records.push_back(make_pair(month,rate));
        }
        float value = loan+down;
        int index = 0;
        loop(month, months+1) {
            if (index < records.size() - 1) {
                if (records[index+1].first <= month) {
                    index++;
                }
            }
            if (month>0) {
                loan -= payment;
            }
            value *= (1-records[index].second);
            if (value > loan) {
                string add_string = (month != 1) ? " months" : " month";
                cout << to_string(month) + add_string + "\n";
                break;
            }
        }
    }
}