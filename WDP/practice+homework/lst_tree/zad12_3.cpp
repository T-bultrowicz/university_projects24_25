#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

pair<bin_tree, int> r_pot(bin_tree t) {
    if(!t) return {NULL,0};
    pair <bin_tree, int> l = r_pot(t->left), r = r_pot(t->right);
    if(l.second == 0 && r.second == 0) {
        t->jump = t;
        return {t, 1};
    }
    if(l.second > r.second) {
        t->jump = l.first;
        return {l.first, l.second + 1};
    } else {
        t->jump = r.first;
        return {r.first, r.second + 1};
    }
} 

void potomek(bin_tree root) {
    r_pot(root);
    return;
}

int main() {
    int a;
    vector<pair <int, int>> b;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    stworz_vector(b, a);
    bin_tree tree = stworz_bin_tree(b);
    auto l = wartosci_infiks(tree);
    for(auto k : l) {
        printf("%d ", k);
    }
    printf("\n");
    potomek(tree);
    printf("%d %d %d", tree->right->jump->val, tree->right->right->jump->val, tree->left->right->jump->val);
    delete tree;
    return 0;
}