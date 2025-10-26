#include<bits/stdc++.h>
using namespace std;

int min_func(int x, int y, int l) {
    if(y == INT_MAX) return x;
    return min(x, y + l);
}

vector<int> banknot(int kwota, const vector<int>& bnkt, const vector<int>& pb) {
    int n = bnkt.size();
    vector<int> res(n, 0);
    if(!kwota) return res;
    long long int dp[n][kwota + 1];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < kwota + 1; j++) {
            dp[i][j] = INT_MAX;
        }
    }
    dp[0][0] = 0;
    for(int i = 1; i <= pb[0]; i++) {
        dp[0][i * bnkt[0]] = i;
    }
    for(int i = 1; i < n; i++) {
        dp[i][0] = 0;
        for(int j = 1; j <= kwota; j++) {
            for(int l = 0; l <= pb[i]; l++) {
                if(j - l * bnkt[i] >= 0) {
                    dp[i][j] = min_func(dp[i][j], dp[i - 1][j - l * bnkt[i]], l);
                } else {
                    break;
                }
            }
        }
    }
    int reszta = kwota, w = dp[n - 1][kwota];
    for(long long int i = n - 2; i >= 0; i--) {
        for(long long int j = 0; j <= pb[i + 1]; j++) {
            if(dp[i][reszta - j * bnkt[i + 1]] + j == w) {
                w -= j;
                reszta -= j * bnkt[i + 1];
                res[i + 1] = j;
                break; 
            }
        }
    }
    res[0] = w;
    return res;
}

int main() {
    int n, d, a, b;
    vector<int> bnkt, res;
    vector<int> b_count;
    scanf("%d %d", &n, &d);
    for(int i = 0; i < d; i++) {
        scanf("%d %d", &a, &b);
        bnkt.push_back(a);
        b_count.push_back(b);
    }
    res = banknot(n, bnkt, b_count);
    for(int i = 0; i < d; i++) {
        printf("Uzyc banknotu o wartosci: %d  -> %d\n", bnkt[i], res[i]);
    }
    return 0;
}