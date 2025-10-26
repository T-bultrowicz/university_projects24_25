#include<cstdlib>
#include<stack>
#include<vector>
#include<cstdio>
using namespace std;

void fill_mine(stack <pair <int,int>> *land, stack <pair <int,int>> *sea, const vector<vector <bool>>& v) {
    for(int i = 0; i < v[0].size(); i++) {
        if(v[0][i]) {
            land->push({0, i});
        } else {
            sea->push({0,i});
        }
        if(v[v.size() - 1][i]) {
            land->push({v.size() - 1, i});
        } else {
            sea->push({v.size() - 1, i});
        }
    }
    for(int j = 0; j < v.size(); j++) {
        if(v[j][0]) {
            land->push({j, 0});
        } else {
            sea->push({j, 0});
        }
        if(v[j][v[0].size() - 1]) {
            land->push({j, v[0].size() - 1});
        } else {
            sea->push({j, v[0].size() - 1});
        }
    }
    return;
} 

int wyspa(const vector<vector<bool>>& v, vector<vector<int>>& pl) {
    int n = v.size(), m = v[0].size(), count = 0;
    stack< pair<int,int>> land_to_visit, sea_to_visit;
    vector< vector <bool>> visited;
    visited.resize(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            visited[i].push_back(false);
        }
    }
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    fill_mine(&land_to_visit, &sea_to_visit, v);
    while(!sea_to_visit.empty() || !land_to_visit.empty()) {
        while(!sea_to_visit.empty()) {
            auto a = sea_to_visit.top();
            visited[a.first][a.second] = true;
            pl[a.first][a.second] = -count;
            sea_to_visit.pop();
            for(int i = 0; i < 4; i++) {
                if(a.first + dx[i] >= 0 && a.first + dx[i] < n && a.second + dy[i] >= 0 && a.second + dy[i] < m) {
                    if(!visited[a.first + dx[i]][a.second + dy[i]]) {
                        if(v[a.first + dx[i]][a.second + dy[i]]) {
                            land_to_visit.push({a.first + dx[i], a.second + dy[i]});
                        } else {
                            sea_to_visit.push({a.first + dx[i], a.second + dy[i]});
                        }
                    }
                }
            }
        }
        if(!land_to_visit.empty()) count++;
        while(!land_to_visit.empty()) {
            auto a = land_to_visit.top();
            visited[a.first][a.second] = true;
            pl[a.first][a.second] = count;
            land_to_visit.pop();
            for(int i = 0; i < 4; i++) {
                if(a.first + dx[i] >= 0 && a.first + dx[i] < n && a.second + dy[i] >= 0 && a.second + dy[i] < m) {
                    if(!visited[a.first + dx[i]][a.second + dy[i]]) {
                        if(v[a.first + dx[i]][a.second + dy[i]]) {
                            land_to_visit.push({a.first + dx[i], a.second + dy[i]});
                        } else {
                            sea_to_visit.push({a.first + dx[i], a.second + dy[i]});
                        }
                    }
                }
            }            
        }
    }
    return count;
}

int main() {
    int a, b, c;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    vector <vector <bool>> mapa;
    vector <vector <int>> zr_mapa;
    mapa.resize(a);
    zr_mapa.resize(a);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(scanf("%d", &c) != 1) {
                return -1;
            }
            mapa[i].push_back((bool) c);
            zr_mapa[i].push_back(0);
        }
    }
    printf("%d\n", wyspa(mapa, zr_mapa));
    printf("\033[1m");
    for(auto i : zr_mapa) {
        for(int j : i) {
            if(j <= 0) {
                printf("\033[44m");
            } else {
                printf("\033[42m");
            }
            printf("%d ", (j >= 0) ? j : -j);
            printf("\033[0m");
        }
        printf("\n");
    }
    return 0;
}