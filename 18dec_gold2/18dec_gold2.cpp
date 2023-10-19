#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<vector<int>> powerset(vector<int> arr) {
    vector< vector<int> > returned;
    for (int i=1; i<32; ++i) {
        vector<int> new_arr;
        int counter = 0;
        int j = i;
        while (j > 0) {
            if (j%2) {
                new_arr.push_back(arr[counter]);
            }
            j /= 2;
            ++counter;
        }
        returned.push_back(new_arr);
    }
    return returned;
}

int main() {
    freopen("cowpatability.in","r",stdin);
    freopen("cowpatability.out","w",stdout);
    int N;
    cin >> N;
    // cout << powerset({1, 2, 3, 4, 5}).size() << endl;
    map< vector<int>,int> occurences;
    vector< vector<int> > flavors;
    // cout << occurences.size() << endl;
    int new_val;
    for (int i=0; i<N; ++i) {
        vector<int> new_flavors;
        for (int j=0; j<5; ++j) {
            cin >> new_val;
            new_flavors.push_back(new_val);
        }
        flavors.push_back(new_flavors);
        // cout << flavors.size() << endl;
        // cout << powerset(new_flavors).size() << endl;
        for (auto& subarr : powerset(new_flavors)) {
            ++occurences[subarr];
        }
    }
    // cout << occurences.size() << endl;
    int compatible = 0;
    for (int i=0; i<N; ++i) {
        for (auto& subarr : powerset(flavors[i])) {
            if (subarr.size()%2) {
                compatible += occurences[subarr] - 1;
            } else {
                compatible -= occurences[subarr] - 1;
            }
        }
    }
    int compatible_pairs = compatible/2;
    int answer = N*(N-1)/2 - compatible_pairs;
    cout << answer;
}