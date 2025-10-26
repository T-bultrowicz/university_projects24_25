#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> flowerbed(x);
    for(int i = 0; i < x; i++) {
        cin >> flowerbed[i];
    }

    int can_place = 0;
    int prev_val = flowerbed[1], prev_prev_val = flowerbed[0];
    if(!prev_val && !prev_prev_val) {
        can_place++;
        prev_val = 1;
    }
    for(size_t i = 2; i < flowerbed.size(); i++) {
        if(!prev_val && !prev_prev_val && !flowerbed[i]) {
            can_place++;
            prev_val = 1;
        }
        prev_prev_val = prev_val;
        prev_val = flowerbed[i]; 
    }
    if(!prev_val && !prev_prev_val) {
        can_place++;
        prev_val = 1;
    }
    cout << (can_place >= n) ? true : false; 
    return 0;
}