#include<bits/stdc++.h>
using namespace std;

int sklejanie(const vector<int>& x) {
    //tworzenie danych
    int n = x.size();
    vector<int>t, dp(n, INT_MAX), tsp(n + 1, 0);
    for(int i = n - 1; i >= 0; i--) {
        t.push_back(x[i]);
    }
    //tablica sum prefiksowych
    tsp[1] = t[0];
    for(int i = 2; i <= n; i++) {
        tsp[i] = tsp[i - 1] + t[i - 1];
    }

    int l = n - 1;
    for(int i = n - 1; i >= 0; i--) {
        //nadanie nowego dp
        dp[i] = (i == n - 1) ? i : min(dp[i], dp[i + 1]);
        //gasienica
        while(tsp[i] - tsp[l] <= tsp[dp[i] + 1] - tsp[i] && l > 0) {
            l--;
        }
        dp[l] = i ? i - 1 : i;
    }
    int k = 0, res = 0;
    while(k < n) {
        k = dp[k];
        k++;
        res++;
    }
    return n - res;
}

int main() {
    int s, d;
    vector<int> x;
    scanf("%d", &s);
    for(int i = 0; i < s; i++) {
        scanf("%d", &d);
        x.push_back(d);
    }
    printf("%d", sklejanie(x));
    return 0;
}