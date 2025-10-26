#include<bits/stdc++.h>
using namespace std;

bool r_search(vector<vector<bool>>& dp, int x, int y, const vector<vector<int>>& t) {
    int n = t.size(), m = t[0].size();
    if(x == n - 1 && y == m - 1) {
        dp[n - 1][m - 1] = true;
        return true;
    }
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for(int i = 0; i < 4; i++) {
        if(x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < m) {
            if(t[x + dx[i]][y + dy[i]] < t[x][y]) {
                if(r_search(dp, x + dx[i], y + dy[i], t)) {
                    dp[x][y] = true;
                    return true;
                }
            }
        }
    }
    return false;
}

int widok(const vector<vector<int>>& t) {
    int n = t.size(), m = t[0].size();
    int res = -1;
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    vector<vector<bool>> dp(n, vector<bool>(m, false));
    r_search(dp, 0, 0, t);
    if(!dp[n - 1][m - 1]) {
        return -1;
    }
    queue<pair<int,int>> to_see;
    to_see.push({0,0});
    dp[0][0] = false;
    while(!to_see.empty()) {
        int x = to_see.front().first;
        int y = to_see.front().second;
        to_see.pop();
        dp[x][y] = false;
        res = max(res, abs(x - y));
        for(int i = 0; i < 4; i++) {
            if(x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < m) {
                if(dp[x + dx[i]][y + dy[i]]) {
                    to_see.push({x + dx[i], y + dy[i]});
                }
            }            
        }
    }
    return res;
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
    printf("%d", widok(x));
    return 0;
}