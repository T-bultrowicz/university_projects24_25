#include<bits/stdc++.h>
using namespace std;

int segment(const vector<int>& t) {
    //tworzenie danych
    int n = t.size();
    int res = INT_MIN;
    int dp[n][n];
    for(int i = 0; i < n; i++) {
        dp[i][i] = t[i];
        res = max(res, t[i]);
    }

    //generowanie segmentow
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < n - i; j++) {
            for(int k = 0; k < i; k++) {
                dp[j][j + i] = -1; 
                if(abs(dp[j][j + k] - dp[j + k + 1][j + i]) == 1) {
                    dp[j][j + i] = max(dp[j][j + k], dp[j + k + 1][j + i]) + 1;
                    res = max(res, dp[j][j + i]);
                }
            }
        }
    }
    //wynik
    return res;
}

int main() {
    int s, d;
    vector<int> x;
    scanf("%d", &s);
    for(int i = 0; i < s; i++) {
        scanf("%d", &d);
        x.push_back(d);
    }
    printf("%d", segment(x));
    return 0;   
}