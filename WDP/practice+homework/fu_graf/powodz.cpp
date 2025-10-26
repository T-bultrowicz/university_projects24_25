#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;


int f_pos(vector <find_union>& t, int v) {
    int l = 0, p = t.size() - 1, mid;
    while(l < p) {
        mid = (l + p) / 2;
        if(t[mid]->val > v) {
            p = mid;
        } else if(t[mid]->val < v) {
            l = mid + 1;
        } else {
            return mid;
        }
    }
    return l;
}

void odwiedz(int x_l, int y_l, const vector<vector<pair<int,bool>>>& q, vector<find_union>& fu, vector<vector <bool>>& visited) {
    if(visited[x_l][y_l]) return;
    int n = q.size(), m = q[0].size();
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    queue<pair<int,int>> to_visit;
    to_visit.push({x_l,y_l});
    while(!to_visit.empty()) {
        int x = to_visit.front().first;
        int y = to_visit.front().second;
        to_visit.pop();
        for(int i = 0; i < 4; i++) {
            if(x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < m) {
                if(!visited[x + dx[i]][y + dy[i]] && q[x + dx[i]][y + dy[i]].first > q[x][y].first) {
                    visited[x + dx[i]][y + dy[i]] = true;
                    to_visit.push({x + dx[i], y + dy[i]});
                    if(q[x + dx[i]][y + dy[i]].second) {
                        unite(fu[f_pos(fu, x_l * m + y_l)], fu[f_pos(fu, (x + dx[i]) * m + y + dy[i])]);
                    }
                }
            }
        }
    }
    return;
}

int powodz(const vector<vector<pair<int,bool>>>& q) {
    int n = q.size(), m = q[0].size(), res = 0, points;
    vector<vector <bool>> visited(n);
    vector<find_union> fu;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            visited[i].push_back(false);
            if(q[i][j].second) {
                fu.push_back(create_find_union(i * m + j));
            }
        }
    }
    for(find_union p : fu) {
        odwiedz(p->val / m, p->val % m, q, fu, visited);
    }
    vector<bool> appear(fu.size(), false);
    for(auto dl : fu) {
        points = find(dl);
        if(!appear[points]) res++;
        appear[points] = true;
    }
    for(auto dl : fu) {
        delete dl;
    }
    return res;
}

int main() {
    int n, m, d;
    if(scanf("%d %d", &n, &m) != 2) {
        return -1;
    }
    vector <vector <pair <int,bool>>> top_map;
    top_map.resize(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(scanf("%d", &d) != 1) {
                return -1;
            }
            top_map[i].push_back({d ,false});
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(scanf("%d", &d) != 1) {
                return -1;
            }
            top_map[i][j].second = (bool) d;
        }
    }
    printf("%d", powodz(top_map));
    return 0;
}