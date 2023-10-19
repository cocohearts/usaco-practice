#include <iostream>
#include <vector>

using namespace std;

int P = 1e9+7;

int two_pow(int exp) {
    int answer = 1;
    int pow = 2;
    while (exp > 0) {
        if (exp%2) {
            answer *= pow;
            answer %= P;
        }
        pow *= pow;
        pow %= P;
        exp /= 2;
    }
    return answer;
}

int strict_lower_bound(vector<int> arr, int item) {
    int lo = 0, hi = arr.size();
    while (hi > lo) {
        int mid = (lo+hi)/2;
        if (arr[mid] <= item) {
            lo = mid+1;
        } else {
            hi = mid;
        }
    }
    return lo;
}

vector<int> insert(vector<int> arr, int item) {
    arr.insert(arr.begin() + strict_lower_bound(arr, item),item);
    // cout << endl;
    return arr;
}

int main() {
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);

    vector<int> left_ends;
    vector<int> right_ends;
    int N;
    cin >> N;
    int answer = 0;
    int left_end, right_end;
    int left_free, right_free;
    for (int i=0; i<N; ++i) {
        cin >> left_end >> right_end;
        left_free = strict_lower_bound(right_ends,left_end);
        right_free = right_ends.size() - strict_lower_bound(left_ends,right_end);
        if (i>0) {
            if (right_end < left_ends[0]) {
                right_free = 0;
            }
            if (left_end > right_ends[right_ends.size()-1]) {
                left_free = right_ends.size();
            }
            answer *= 2;
        }
        answer += two_pow(left_free+right_free);
        answer %= P;
        // cout << answer << endl;
        left_ends = insert(left_ends,left_end);
        right_ends = insert(right_ends,right_end);
    }
    cout << answer;
}