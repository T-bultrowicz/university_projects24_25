#include<bits/stdc++.h>
using namespace std;

vector<int> energia(int k, int e, int n, int* t) {
    //tworzenie tablic dp i tsp - sum prefiksowych od t
    vector<vector <vector <bool>>> dp(n + 1, vector<vector<bool>>(k + 2, vector<bool>(e + 1, false)));
    dp[0][0][0] = true;
    int tsp[n + 1];
    tsp[0] = 0;
    for(int i = 1; i <= n; i++) {
        tsp[i] = tsp[i - 1] + t[i - 1];
    }

    //napełnianie tablicy dp
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= min(k, i); j++) {
            int x = tsp[j] - tsp[0];
            int y = min(tsp[i] - tsp[i - j], e);
            for(int l = x; l <= y; l++) {
                if(l + t[i] < e + 1 && dp[i][j][l]) {
                    dp[i + 1][j + 1][l + t[i]] = dp[i][j][l];
                }
                if(dp[i][j][l]) dp[i + 1][j][l] = dp[i][j][l];
            }
        }
    }
    vector<int> res, right_order_res;
    if(!dp[n][k][e]) {
        return res;
    }

    //odczytywanie ruchow
    int powloka = n, energia = e;
    for(int pozostalo = k; pozostalo > 0; pozostalo--) {
        while(dp[powloka - 1][pozostalo][energia]) {
            powloka--;
        }
        powloka--;
        energia -= t[powloka];
        res.push_back(powloka);
    }

    //obroc res
    for(int i = res.size() -1 ; i>= 0; i--) {
        right_order_res.push_back(res[i]);
    }
    //zwroc
    return right_order_res;
}

int main() {
    int k, e, sizet;
    scanf("%d %d %d", &k, &e, &sizet);
    int t[sizet];
    for(int i = 0; i < sizet; i++) {
        scanf("%d", t + i);
    }
    printf("\n");
    vector<int>res = energia(k, e, sizet, t);
    for(int a: res) {
        printf("%d ", a);
    }
    return 0;
}