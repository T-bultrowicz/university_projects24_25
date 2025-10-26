#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

void r_fast(bin_tree t, bin_tree *pin_to) {
    if(!t) return;
    r_fast(t->right, pin_to);
    t->jump = *pin_to;
    *pin_to = t;
    r_fast(t->left, pin_to);
    return;
}

void fastryguj(bin_tree root) {
    bin_tree pin_to = NULL;
    r_fast(root, &pin_to);
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
    fastryguj(tree);
    printf("%d %d %d", tree->left->left->jump->val, tree->right->left->jump->val, tree->left->jump->val);
    delete tree;
    return 0;
}