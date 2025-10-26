#include<bits/stdc++.h>
#include"find_union.h"
using namespace std;

vector<int> malpki(pair <int,int> tab[], int il_m, int il_r) {
    vector<int> malp(il_m, -1);
    vector<find_union> fu;
    for(int i = 0; i < il_m; i++) {
        fu.push_back(create_find_union(i));
    }
    for(int j = il_r - 1; j >= 0; j--) {
        if(find(fu[tab[j].first]) == 0) {
            if(find(fu[tab[j].second]) != 0) {
                for(int a : elems(fu[tab[j].second])) {
                    malp[a] = j;
                }
            }
            unite(fu[tab[j].first], fu[tab[j].second]);
        } else {
            if(find(fu[tab[j].second]) == 0) {
                for(int a : elems(fu[tab[j].first])) {
                    malp[a] = j;
                }
            }
            unite(fu[tab[j].second], fu[tab[j].first]);
        }
    }
    for(int i = 0; i < il_m; i++) {
        delete fu[i];
    }
    return malp;
}


int main() {
    int il_m, il_r;
    if(scanf("%d %d", &il_m, &il_r) != 2) {
        return -1;
    }
    pair<int,int> rozl[il_r];
    for(int i = 0; i < il_r; i++) {
        if(scanf("%d %d", &(rozl[i].first), &(rozl[i].second)) != 2) {
            return -1;
        }
        rozl[i].first--;
        rozl[i].second--;
    }
    vector<int> momenty = malpki(rozl, il_m, il_r);
    printf("\n");
    for(int i = 0; i < momenty.size(); i++) {
        printf("Malpka %d spadla w momencie %d\n", i+1, momenty[i]);
    }
    printf("\n");
    return 0;
}