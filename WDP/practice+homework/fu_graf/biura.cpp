#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;

//T: O(E^2), M:O(E^2)
vector <vector <int>> przetworz(const vector <vector <int>>& g) {
    vector<vector <int>> res(g.size());
    vector<bool> pom;
    for(int i = 0; i < g.size(); i++) {
        pom.assign(g[0].size(), false);
        for(int b : g[i]) {
            pom[b] = true;
        }
        for(int j = 0; j < g.size(); j++) {
            if(!pom[j]) {
                res[i].push_back(j);
            }
        }
    }
    return res;
}

vector<vector <int>> biura(const vector <vector <int>>& g) {
    auto nowy_g = przetworz(g);
    vector<find_union> fu;
    vector<vector<int>> res(g.size());
    for(int i = 0; i < g.size(); i++) {
        fu.push_back(create_find_union(i));
    }
    for(int i = 0; i < nowy_g.size(); i++) {
        for(int j : nowy_g[i]) {
            unite(fu[i], fu[j]);
        }
    }
    for(int i = 0; i < g.size(); i++) {
        res[find(fu[i])].push_back(i);
    }
    for(int i = 0; i < g.size(); i++) {
        delete fu[i];
    }
    return res;
}


int main() {
    int n, m;
    if(scanf("%d %d", &n, &m) != 2) {
        return -1;
    }
    vector <vector <int>> graph, grupy;
    int a, b;
    graph.resize(n);
    for(int i = 0; i < m; i++) {
        if(scanf("%d %d", &a, &b) != 2) {
            return -1;
        }
        graph[--a].push_back(--b);
        graph[b].push_back(a);
    }
    grupy = biura(graph);
    printf("\n");
    for(auto a_a : grupy) {
        for(int b_b : a_a) {
            printf("%d ", ++b_b);
        }
        if(a_a.size()) {
            printf("\n");
        }
    } 
    return 0;
}