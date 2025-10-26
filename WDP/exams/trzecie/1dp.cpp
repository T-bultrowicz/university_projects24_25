#include<cstdlib>
#include<cstdio>

int ile_rozlozen(int l) {
    if(l < 0) return 0;
    int dp[l + 1];
    dp[0] = 1, dp[1] = 1;
    for(int i = 2; i <= l; i++) {
        dp[i] = dp[i - 2];
        dp[i] += dp[i / 2];
    }
    return dp[l];
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", ile_rozlozen(n));
    return 0;
}