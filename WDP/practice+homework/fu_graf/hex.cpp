#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;


int hex(int n, const vector <pair <int,int>>& moves) {
    if(n == 1) return 1;
    int tab[n][n];
    int res = 0, dual = 0;
    vector<find_union> fu_dol, fu_gor;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            tab[i][j] = 0;
            fu_dol.push_back(create_find_union(i * n + j));
            fu_gor.push_back(create_find_union(i * n + j));
        }
    }
    for(auto mov : moves) {
        tab[mov.first][mov.second] = (++res % 2) ? 1 : -1;
        if(mov.first > 0) {
            if(mov.second > 0) {
                if(tab[mov.first - 1][mov.second - 1] == tab[mov.first][mov.second]) {
                    unite(fu_dol[(mov.first - 1) * n + (mov.second - 1)], fu_dol[mov.first * n + mov.second]);
                    unite(fu_gor[mov.first * n + mov.second], fu_gor[(mov.first - 1) * n + (mov.second - 1)]);                
                }
            }
            if(tab[mov.first - 1][mov.second] == tab[mov.first][mov.second]) {
                unite(fu_dol[(mov.first - 1) * n + mov.second], fu_dol[mov.first * n + mov.second]);
                unite(fu_gor[mov.first * n + mov.second], fu_gor[(mov.first - 1) * n + mov.second]);
            }
        }
        if(mov.first < n - 1) {
            if(mov.second < n - 1) {
                if(tab[mov.first + 1][mov.second + 1] == tab[mov.first][mov.second]) {
                    unite(fu_dol[mov.first * n + mov.second], fu_dol[(mov.first + 1) * n + (mov.second + 1)]);
                    unite(fu_gor[(mov.first + 1) * n + (mov.second + 1)], fu_gor[mov.first * n + mov.second]);
                }
            }
            if(tab[mov.first + 1][mov.second] == tab[mov.first][mov.second]) {
                unite(fu_dol[mov.first * n + mov.second], fu_dol[(mov.first + 1) * n + mov.second]);
                unite(fu_gor[(mov.first + 1) * n + mov.second], fu_gor[mov.first * n + mov.second]);
            }
        }
        if(mov.second > 0) {
            if(tab[mov.first][mov.second] == tab[mov.first][mov.second - 1]) {
                unite(fu_dol[mov.first * n + (mov.second - 1)], fu_dol[mov.first * n + mov.second]);
                unite(fu_gor[mov.first * n + mov.second], fu_gor[mov.first * n + (mov.second - 1)]);
            }
        }
        if(mov.second < n - 1) {
            if(tab[mov.first][mov.second] == tab[mov.first][mov.second + 1]) {
                unite(fu_dol[mov.first * n + mov.second], fu_dol[mov.first * n + (mov.second + 1)]);
                unite(fu_gor[mov.first * n + (mov.second + 1)], fu_gor[mov.first * n + mov.second]);
            }
        }
        if(find(fu_dol[mov.first * n + mov.second]) < n && find(fu_gor[mov.first * n + mov.second]) >= (n - 1)* n && tab[mov.first][mov.second] == -1) {
            dual = res;
            break;
        }
        if(find(fu_dol[mov.first * n + mov.second]) % n == 0 && find(fu_gor[mov.first * n + mov.second]) % n == n - 1 && tab[mov.first][mov.second] == 1) {
            dual = res;
            break;
        } 
    }
    for(auto a: fu_dol) {
        delete a;
    }
    for(auto a: fu_gor) {
        delete a;
    }
    return dual;
}

int main() {
    vector <pair <int,int>> moves;
    int n, m;
    if(scanf("%d %d", &n, &m) != 2) {
        return -1;
    }
    moves.resize(m);
    for(int i = 0; i < m; i++) {
        if(scanf("%d %d", &(moves[i].first), &(moves[i].second)) != 2) {
            return -1;
        }
        moves[i].first--;
        moves[i].second--;
    }
    printf("%d", hex(n, moves));
    return 0;
}