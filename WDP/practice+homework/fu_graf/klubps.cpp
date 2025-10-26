#include<bits/stdc++.h>
using namespace std;

pair <int,int> r(int x, int y, int d) {
    if(!d) {
        return {x + 1, y};
    } else if(d == 1) {
        return {x, y + 1};
    } else if(d == 2) {
        return {x - 1, y};
    }
    return {x, y - 1};
}

bool klubps(vector <vector <vector <bool>>>& ul) {
    if(!ul[0][0][0]) return false;
    int x = ul.size(), y = ul[0].size(), curr_turn = 0;
    int mt_x, mt_y;
    vector <vector <vector <bool>>> visited;
    stack <vector <int>> to_visit;
    visited.resize(x);
    for(int i = 0; i < x; i++) {
        visited[i].resize(y);
        for(int j = 0; j < y; j++) {
            for(int k = 0; k < 3; k++) {
                visited[i][j].push_back(false);
            }
        }
    }
    to_visit.push({0, 0, 0});
    while(!to_visit.empty()) {
        vector <int> t = to_visit.top();
        if((t[0] == x - 2 && t[1] == y - 1 && t[2] == 0) || (t[0] == x - 1 && t[1] == y - 2 && t[2] == 1)) {
            return true;
        }
        visited[t[0]][t[1]][t[2]] = true;
        to_visit.pop();
        mt_x = r(t[0], t[1], t[2]).first;
        mt_y = r(t[0], t[1], t[2]).second;
        if(ul[mt_x][mt_y][t[2]] && !visited[mt_x][mt_y][t[2]]) {
            to_visit.push({mt_x, mt_y, t[2]});
        }
        if(ul[mt_x][mt_y][(t[2] + 1) % 4] && !visited[mt_x][mt_y][(t[2] + 1) % 4]) {
            to_visit.push({mt_x, mt_y, (t[2] + 1) % 4});
        } 
    }
    return false;
}


int main() {
    int a, b, il_drg;
    if(scanf("%d %d %d", &a, &b, &il_drg) != 3) {
        return -1;
    }
    vector <vector <vector <bool>>> ulice;
    ulice.resize(a);
    for(int i = 0;i < a; i++) {
        ulice[i].resize(b);
        for(int j = 0; j < b; j++) {
            for(int k = 0;k < 3; k++) {
                ulice[i][j].push_back(false);
            }
        }
    }
    int j, d, t;
    for(int k = 0; k < il_drg; k++) {
        if(scanf("%d %d %d", &j, &d, &t) != 3) {
            return -1;
        }
        ulice[j][d][t] = true;
        ulice[r(j,d,t).first][r(j,d,t).second][(t + 2) % 4] = true;
    }
    if(klubps(ulice)) {
        printf("yessir");
    } else {
        printf("no");
    }
    return 0;
}