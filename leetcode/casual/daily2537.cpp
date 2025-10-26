#include<bits/stdc++.h>
using namespace std;

long long countGood(vector<int>& nums, int k) {
    size_t t = nums.size(), res = 0;
    if(k == 0) {
        return (t * (t + 1)) >> 1;
    }
    unordered_map<int,int> mp;
    int l = 0, r = 0, found_con = 0;
    bool found;
    while(r < t) {
        found = false;
        auto x = mp.find(nums[r]);
        if(x != mp.end()) {
            found_con += x->second++;
        } else {
            mp.insert({nums[r], 1});
        }

        if(found_con >= k) found = true;
        while(found_con >= k) {
            x = mp.find(nums[l]);
            found_con -= --x->second;
            if(!x->second) {
                mp.erase(x);
            }
            l++;
        }
        if(found) {
            res += l--;
        }
        r++;
    }
    return res;
}


int main() {
    int x, k;
    cin >> x >> k;
    vector <int> t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << countGood(t, k);
}