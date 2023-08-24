#include <cmath>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    int N;
    cin >> N;
    vector<int> locations(N);
    for (int i = 0; i<N; ++i) {
        // cin >> loc;
        cin >> locations[i];
        locations[i] *= 2;
    }
    sort(locations.begin(),locations.end());

    vector<int> explode_left(N);
    vector<int> explode_right(N);

    explode_left[0] = 0;
    explode_right[0] = 0;
    int prev_max_index = 0;
    for (int i=1; i<N; ++i) {
        if (locations[i] - locations[i-1] <= explode_left[i-1]+1) {
            //explode_left[i]+1 suffices, explode_left[i] is necessary; 
            if (locations[i] - locations[prev_max_index] <= explode_left[i-1]) {
                explode_left[i] = explode_left[i-1];
            } else {
                explode_left[i] = explode_left[i-1] + 2;
                prev_max_index = i-1;
            }
        } else {
            explode_left[i] = locations[i] - locations[i-1];
        }
    }    
    reverse(locations.begin(),locations.end());
        
    prev_max_index = 0;
    for (int i=1; i<N; ++i) {
        if (locations[i-1] - locations[i] <= explode_right[i-1]+1) {
            //explode_right[i]+1 suffices, explode_right[i] is necessary; 
            if (locations[prev_max_index] - locations[i] <= explode_right[i-1]) {
                explode_right[i] = explode_right[i-1];
            } else {
                explode_right[i] = explode_right[i-1] + 2;
                prev_max_index = i-1;
            }
        } else {
            explode_right[i] = locations[i-1] - locations[i];
        }
    }    
    reverse(locations.begin(),locations.end());
    reverse(explode_right.begin(),explode_right.end());

    // now binary search for R
    int lo = 0;
    int hi = locations[N-1];
    while (lo<hi) {
        int mid = (lo+hi)/2;
        if (mid < 2) {
            if (N==1) {
                hi == mid;
            } else {
                lo = mid+1;
            }
            continue;
        }
        int right_index = N-(upper_bound(explode_right.rbegin(),explode_right.rend(),mid-2) - explode_right.rbegin());
        int left_index = upper_bound(explode_left.begin(),explode_left.end(),mid-2) - explode_left.begin()-1;
        int distance = locations[right_index] - locations[left_index];
        // cout << mid << left_index << right_index << endl;
        // cout << lo << hi << distance << endl;
        if (distance <= 2*mid) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    int answer = lo;

    // int lo = 0;
    // while (explode_right[lo] > explode_left[lo]) {++lo;}
    // int answer = max({locations[lo]-locations[lo-1],2*explode_left[lo-1]+2,2*explode_right[lo]+2});
    // answer = min({answer,2*explode_left[lo],2*explode_right[lo-1]});
    cout << answer/2 << "." << (answer % 2 ? 5 : 0) << endl;
}