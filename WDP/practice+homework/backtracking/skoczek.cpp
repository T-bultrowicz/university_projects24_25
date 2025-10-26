#include<bits/stdc++.h>
using namespace std;

bool r_horsey(int x, int y, int s, int left, vector<vector<bool>>& v, vector<pair<int,int>>& m) {
    if(left == 0) {
        m.push_back({x, y});
        return true;
    }
    v[x][y] = true;
    for(int i = -2; i < 0; i++) {
        if(x + i >= 0 && x + i < s && y + 3 + i >= 0 && y + 3 + i < s) {
            if(!v[x + i][y + 3 + i]) {
                if(r_horsey(x + i, y + 3 + i, s, left - 1, v, m)) {
                    m.push_back({x,y});
                    return true;
                }
            }
        }
        if(x + i >= 0 && x + i < s && y - 3 - i >= 0 && y - 3 - i < s) {
            if(!v[x + i][y - 3 - i]) {
                if(r_horsey(x + i, y - 3 - i, s, left - 1, v, m)) {
                    m.push_back({x,y});
                    return true;
                }
            }           
        }
    }
    for(int i = 1; i < 3; i++) {
        if(x + i >= 0 && x + i < s && y + 3 - i >= 0 && y + 3 - i < s) {
            if(!v[x + i][y + 3 - i]) {
                if(r_horsey(x + i, y + 3 - i, s, left - 1, v, m)) {
                    m.push_back({x,y});
                    return true;
                }
            }
        }
        if(x + i >= 0 && x + i < s && y - 3 + i >= 0 && y - 3 + i < s) {
            if(!v[x + i][y - 3 + i]) {
                if(r_horsey(x + i, y - 3 + i, s, left - 1, v, m)) {
                    m.push_back({x,y});
                    return true;
                }
            }
        }        
    }
    v[x][y] = false;
    return false;
}

vector<pair<int,int>> skoczek(int n) {
    vector<vector<bool>> byl;
    vector<pair<int,int>> moves;
    byl.resize(n);
    for(int i = 0; i < n; i++) {
        byl[i].resize(n, false);
    }
    byl[0][0] = true;
    r_horsey(0, 0, n, n * n - 1, byl, moves);
    return moves;
}


int main() {
    int n;
    scanf("%d", &n);
    vector<pair<int,int>> horsey = skoczek(n);
    for(auto a: horsey) {
        printf("%d %d\n", a.first, a.second);
    }
    return 0;
}