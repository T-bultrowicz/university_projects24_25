#include<bits/stdc++.h>
using namespace std;

long long int sklejenie(int j, int k, int i, vector<long long int>& tsp, vector<vector<long long int>>& dp) {
    long long int res = dp[j][j + k] + dp[j + k + 1][j + i];
    res += max(tsp[j + k] - ((j - 1 >= 0) ? tsp[j - 1] : 0), tsp[j + i] - tsp[j + k]);
    return res;
}

long long int kijek(const vector<int>& x) {
    //generowanie danych
    long long int n = x.size();
    vector<vector<long long int>> dp(n, vector<long long int>(n, INT_MAX));
    vector<long long int> tsp(n, 0);
    tsp[0] = x[0];
    dp[0][0] = 0;
    for(long long int i = 1; i < n; i++) {
        tsp[i] = tsp[i - 1] + x[i];
        dp[i][i] = 0;
    }

    //wypełnianie danych
    for(long long int i = 1; i < n; i++) {
        for(long long int j = 0; j < n - i; j++) {
            for(long long int k = 0; k < i; k++) {
                dp[j][j + i] = min(dp[j][j + i], sklejenie(j, k, i, tsp, dp));
            }
        }
    }

    //zwrot
    return dp[0][n - 1];
}


int main() {
    int s, d;
    vector<int> x;
    scanf("%d", &s);
    for(int i = 0; i < s; i++) {
        scanf("%d", &d);
        x.push_back(d);
    }
    printf("%lld", kijek(x));
    return 0;
}