#include<bits/stdc++.h>
using namespace std;

long long putMarbles(vector<int>& weights, int k) {
    size_t s = weights.size();
    vector<int> con_sums(s - 1);
    for(size_t i = 0; i < s - 1; i++) {
        con_sums[i] = weights[i] + weights[i + 1];
    }
    long long sum_min = 0, sum_max = 0;
    sort(con_sums.begin(), con_sums.end());
    for(int j = 0; j < k - 1; j++) {
        sum_min += con_sums[j];
        sum_max += con_sums[s - j - 2];
    }
    return sum_max - sum_min;
}

int main() {
    int x, k;
    cin >> x >> k;
    vector<int> t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << putMarbles(t, k);
    return 0;
}
