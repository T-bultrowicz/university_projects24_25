#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;

int znaj_brzeg(vector<bool>& st_s, vector<pair<int,int>>& d, int m, int cor) {
    int drv[] = {m, -m, -1, 1}; 
    for(int j = 0; j < 4; j++) {
        if((cor % m == 0 && j == 2) || (cor % m == m - 1 && j == 3) ||
            (cor < m && j == 1) || (cor >= d.size() - m && j == 0)) {
                continue;
            }
        if(st_s[cor + drv[j]]) {
            if(cor + drv[j] % m == 0 || cor + drv[j] % m == m - 1 || cor + drv[j] < m || cor + drv[j] >= d.size() - m) {
                return cor + drv[j];
            }
        }
    }
    return cor;
}

int sadzawka(const vector<vector <int>>& mapa, int jas_x, int jas_y) {
    int n = mapa.size(), m = mapa[0].size();
    int drv[] = {m, -m, -1, 1};
    vector<find_union> fu;
    vector<bool> st_s;
    vector<pair <int, int>> d; 
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            fu.push_back(create_find_union(i * m + j));
            d.push_back({mapa[i][j], i * m + j});
            st_s.push_back(false);
        }
    }
    sort(d.begin(), d.end());
    for(int i = d.size() - 1; i >= 0; i--) {
        st_s[d[i].second] = true;
        int con_to = znaj_brzeg(st_s, d, m, d[i].second);
        for(int j = 0; j < 4; j++) {
            if((d[i].second % m == 0 && j == 2) || (d[i].second % m == m - 1 && j == 3) ||
                (d[i].second < m && j == 1) || (d[i].second >= d.size() - m && j == 0)) {
                    continue;
                }
            if(st_s[d[i].second + drv[j]]) {
                unite(fu[con_to], fu[d[i].second + drv[j]]);
            }
        }
        int res = find(fu[jas_x * m + jas_y]);
        if(res % m == 0 || res % m == m - 1 || res < m || res >= d.size() - m) {
            for(auto del : fu) {
                delete del;
            }
            return d[i].first;
        }
    }
    for(auto del : fu) {
        delete del;
    }
    return 0;
}

int main() {
    int a, b, c;
    int d, e;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    vector <vector <int>> mapa;
    mapa.resize(a);
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(scanf("%d", &c) != 1) {
                return -1;
            }
            mapa[i].push_back(c);
        }
    }
     if(scanf("%d %d", &d, &e) != 2) {
        return -1;
    }   
    assert(d < a && e < b);
    printf("%d", sadzawka(mapa, d, e));
    return 0;
}