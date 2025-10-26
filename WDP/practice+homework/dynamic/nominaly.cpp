#include<bits/stdc++.h>
using namespace std; 


int nominaly(int n, const vector<int>& bnkt) {
    if(!n) return 0;
    vector<int>dp(n + 1, 0);
    dp[0] = 1;
    for(int j : bnkt) {
        for(int i = 0; i < n + 1; i++) {
            if(i - j >= 0) {
                dp[i] += dp[i - j];
            }
        }
    }
    return dp[n];
}

int main() {
    int n, d;
    scanf("%d %d", &n, &d);
    vector<int>bnkt(d);
    for(int i = 0; i < d; i++) {
        scanf("%d", &bnkt[i]);
    }
    printf("%d ", nominaly(n, bnkt));
    return 0;
}