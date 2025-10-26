#include<bits/stdc++.h>
using namespace std;

int transf(int pos, int prev_pos, int* dp, bool* used) {
    int res;
    int x = (dp[pos] == -1) ? INT_MAX - 3: dp[pos];
    int y = (dp[prev_pos] == -1) ? INT_MAX - 2 : dp[prev_pos];
    if(!used[prev_pos]) y++;
    if(y <= x) {
        res = y;
        used[pos] = true;
    } else {
        res = x;
    }
    return (res == INT_MAX - 3) ? -1 : res;
}


int banknot(int n, const vector<int>& bnkt) {
    if(!n) return 0;
    int dp[n + 1];
    bool used[n + 1];
    for(int i = 0; i < n + 1; i++) {
        used[i] = false;
        if(i % bnkt[0]) {
            dp[i] = -1;
        } else {
            dp[i] = 1;
        }
    }    
    for(int bn : bnkt) {
        if(bn == bnkt[0]) continue;
        dp[0] = 1;
        used[0] = true;
        for(int j = 1; j < n + 1; j++) {
            used[j] = false;
            if(j - bn >= 0) {
                dp[j] = transf(j, j - bn, dp, used);
            }
        }
    }
    return dp[n];
}

int main() {
    int n, d, a;
    vector<int> bnkt;
    scanf("%d %d", &n, &d);
    for(int i = 0; i < d; i++) {
        scanf("%d", &a);
        bnkt.push_back(a);
    }
    printf("%d", banknot(n, bnkt));
    return 0;
}