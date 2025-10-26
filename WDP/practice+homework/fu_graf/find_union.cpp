#include<vector>
#include<cstdio>
#include<queue>
#include "find_union.h"

find_union create_find_union(int v) {
    find_union res = new node;
    res->val = v;
    res->equal = res;
    return res;
}

int find(find_union f) {
    find_union target = f, f2 = f;
    while(target->equal != target) {
        target = target->equal;
    }
    while(f2->equal != f2) {
        f = f2->equal;
        f2->equal = target;
        f2 = f;
    }
    return target->val;
}

bool equivalent(find_union f, find_union g) {
    return (find(f) == find(g));
}

void unite(find_union f, find_union g) {
    if(equivalent(f,g)) return;
    find_union g_cp = g, corr = g;
    while(g_cp->equal != g_cp) {
        g_cp = g_cp->equal;
    }
    while(corr != corr->equal) {
        g = corr->equal;
        corr->equal = g_cp;
        corr = g;
    }
    f->childs.push_back(g_cp);
    g_cp->equal = f;
    return;
}

int size(find_union f) {
    int res = 1;
    std::queue<find_union> to_see;
    find_union f_cp = f;
    while(f_cp->equal != f_cp) {
        f_cp = f_cp->equal;
    } 
    to_see.push(f_cp);
    while(!to_see.empty()) {
        find_union h = to_see.front();
        for(auto l : h->childs) {
            to_see.push(l);
            res++;
        }
        to_see.pop();
    }
    return res;
}

std::vector<int> elems(find_union f) {
    std::vector <int> res;
    std::queue<find_union> to_see;
    find_union f_cp = f;
    while(f_cp->equal != f_cp) {
        f_cp = f_cp->equal;
    } 
    to_see.push(f_cp);
    res.push_back(f_cp->val);
    while(!to_see.empty()) {
        find_union h = to_see.front();
        for(auto l : h->childs) {
            to_see.push(l);
            res.push_back(l->val);
        }
        to_see.pop();
    }
    return res;
}