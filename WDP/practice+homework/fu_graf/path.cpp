#include<bits/stdc++.h>
using namespace std;


int r_pat(vector <int>& val, const vector <vector <int>>& graph, int vertex) {
    if(val[vertex] != -1) {
        return val[vertex];
    }
    int res = -1;
    for(int con : graph[vertex]) {
        if(con > vertex) {
            res = max(res, r_pat(val, graph, con));
        }
    }
    return res + 1;
}

int path(const vector <vector <int>>& graph) {
    vector <int> values;
    int res = 0;
    for(int i = 0; i < graph.size(); i++) {
        values.push_back(-1);
    }
    for(int i = 0; i < graph.size(); i++) {
        if(values[i] == -1) {
            values[i] = r_pat(values, graph, i);
        }
        res = max(res, values[i]);
    }
    return res;
}

int main() {
    int n, m;
    if(scanf("%d %d", &n, &m) != 2) {
        return -1;
    }
    vector <vector <int>> graph;
    int a, b;
    graph.resize(n);
    for(int i = 0; i < m; i++) {
        if(scanf("%d %d", &a, &b) != 2) {
            return -1;
        }
        graph[--a].push_back(--b);
        graph[b].push_back(a);
    }
    printf("%d", path(graph));  
    return 0;
}