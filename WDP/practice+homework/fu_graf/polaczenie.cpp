#include<bits/stdc++.h>
using namespace std;

typedef vector<vector <int>> graph;

void broad_fs(const graph& g, int v, vector<int>& res) {
    queue<pair<int,int>> to_visit;
    to_visit.push({v,0});
    while(!to_visit.empty()) {
        auto w = to_visit.front();
        res[w.first] = w.second;
        to_visit.pop();
        for(int el : g[w.first]) {
            if(res[el] == -1) {
                to_visit.push({el, w.second + 1});
                res[el] = 0;
            }
        }
    }
}

int polaczenie(const graph& g, int u, int v, int w) {
    vector<int> from_u(g.size(), -1), from_v(g.size(), -1), from_w(g.size(), -1);
    broad_fs(g, u, from_u);
    broad_fs(g, v, from_v);
    queue <pair<int,int>> to_visit;
    to_visit.push({w, 0});
    int res = INT_MAX;
    while(!to_visit.empty()) {
        auto p = to_visit.front();
        if(from_u[p.first] != -1 && from_v[p.first] != -1) {
            res = min(res, from_u[p.first] + from_v[p.first] + p.second);
        }
        to_visit.pop();
        for(int el : g[p.first]) {
            if(from_w[el] == -1) {
                to_visit.push({el, p.second + 1});
                from_w[el] = 0;
            }
        }
    }
    return (res == INT_MAX) ? -1 : res;
}


int main() {
    int n, m;
    int u, v, w;
    if(scanf("%d %d %d %d %d", &n, &m, &u, &v, &w) != 5) {
        return -1;
    }
    u--, v--, w--;
    graph graph_;
    int a, b;
    graph_.resize(n);
    for(int i = 0; i < m; i++) {
        if(scanf("%d %d", &a, &b) != 2) {
            return -1;
        }
        graph_[--a].push_back(--b);
        graph_[b].push_back(a);
    }
    printf("%d", polaczenie(graph_, u, v, w));  
    return 0;
}