#include<bits/stdc++.h>
using namespace std;

int maximumCandies(vector<int>& t, long long k) {
    int l = 0, r = 10e7, mid;
    long long how_many = 0;
    while(l < r) {
        mid = (l + r + 1) / 2;
        for(int i : t) {
            how_many += i / mid;
        }
        if(how_many >= k) {
            l = mid;
        } else {
            r = mid - 1;
        }
        how_many = 0;
    }
    return l;
}

int main() {
    int x;
    long long k;
    cin >> x >> k;
    vector<int> t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << maximumCandies(t, k);
    return 0;
}