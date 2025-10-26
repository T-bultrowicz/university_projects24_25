#include<bits/stdc++.h>
using namespace std; 


int unikat(const vector<int>& b, int k) {
    if(!k) return 0;
    vector<int>dp(k + 1, 0);
    dp[0] = 1;
    for(int j : b) {
        for(int i = 0; i < k + 1; i++) {
            if(i - j >= 0) {
                dp[i] += dp[i - j];
            }
        }
    }
    for(int l = k - 1; l >=0 ; l--) {
        if(dp[l] == 1) return l;
    }
    return 0;
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    vector<int>bnkt(d);
    for(int i = 0; i < d; i++) {
        scanf("%d", &bnkt[i]);
    }
    printf("%d ", unikat(bnkt, n));
    return 0;
}