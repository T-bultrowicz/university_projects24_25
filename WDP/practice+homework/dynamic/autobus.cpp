#include<bits/stdc++.h>
using namespace std;

int autobus(const vector<vector<int>>& x) {
    //tworzenie danych
    int n = x.size(), m = x[0].size();
    vector<int>dp(m, 0);
    dp[0] = x[0][0];
    for(int i = 1; i < m; i++) {
        dp[i] = dp[i - 1] + x[0][i];
    }

    //zgarnianie pasazerow
    for(int i = 1; i < n; i++) {
        dp[0] += x[i][0];
        for(int j = 1; j < m; j++) {
            dp[j] = max(dp[j], dp[j - 1]) + x[i][j];
        }
    }
    return dp[m - 1];
}


int main() {
    int n, m, d;
    vector<vector <int>> x;
    scanf("%d %d", &n, &m);
    x.resize(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &d);
            x[i].push_back(d);
        }
    }
    printf("%d", autobus(x));
    return 0;
}