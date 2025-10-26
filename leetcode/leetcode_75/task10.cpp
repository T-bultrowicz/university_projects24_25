#include<bits/stdc++.h>
using namespace std;

int main() {
    int x;
    cin >> x;
    vector<int> nums(x);
    for(int i = 0; i < x; i++) {
        cin >> nums[i];
    }

    int i = 0;
    for(int j = 0; j < nums.size(); j++) {
        if(nums[j]) {
            nums[i] = nums[j];
            i++;
        }
    }
    for(int k = i; k < nums.size(); k++) {
        nums[k] = 0;
    }
    for(int a : nums) {
        cout << a << " ";
    }
    return 0;
}