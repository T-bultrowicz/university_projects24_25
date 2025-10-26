#include<bits/stdc++.h>
using namespace std;

int longestOnes(vector<int>& r, int k) {
    int flips = k, left = 0, right = 0, s = r.size();
    while(right < s && flips) {
        if(!r[right++]) flips--;
    }
    while(right < s && r[right]) {
        right++;
    }
    int longest_one = right - left;
    while(right < s) {
        if(flips) {
            if(!r[right++]) flips--;
        } else {
            if(r[right]) {
                right++;
            }
            else if(!r[left++]) flips++;
        }
        longest_one = max(longest_one, right - left);
    }
    return longest_one;
}

int main() {
    int x, k;
    cin >> x >> k;
    vector<int>t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << longestOnes(t, k);
    return 0;
}