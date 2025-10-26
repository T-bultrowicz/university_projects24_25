#include<bits/stdc++.h>
using namespace std;

double findMaxAverage(vector<int>& nums, int k) {
    int sum = 0;
    for(int i = 0; i < k; i++) {
        sum += nums[i];
    }
    int max_sum = sum;
    for(int j = k; j < nums.size(); j++) {
        sum -= nums[j - k];
        sum += nums[j];
        max_sum = max(sum, max_sum);
    }
    return (double) max_sum / k;
}

int main() {
    int x, k;
    cin >> x >> k;
    vector<int>t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << findMaxAverage(t, k);
    return 0;
}